//
// Created by hyq on 10/29/23.
//

#include "sql/expr/tuple.h"
#include "sql/operator/sort_physical_operaotr.h"
#include "sql/stmt/orderby_stmt.h"
#include <algorithm>
#include <thread>

RC SortPhysicalOperator::open(Trx *trx)
{
  RC rc = RC::SUCCESS;
  if (RC::SUCCESS != (rc = children_[0]->open(trx))) {
    rc = RC::INTERNAL;
    LOG_WARN("SortOperater child open failed!");
  }
  return rc;
}

typedef std::pair<std::vector<Value>, int> CmpPair;

void parallel_sort(std::vector<CmpPair> &data, size_t num_threads, const bool *order)
{
  size_t                   chunk_size = data.size() / num_threads;
  std::vector<std::thread> threads;

  auto cmp = [&order](const CmpPair &a, const CmpPair &b) {
    auto &cells_a = a.first;
    auto &cells_b = b.first;
    assert(cells_a.size() == cells_b.size());
    for (size_t i = 0; i < cells_a.size(); ++i) {
      auto &cell_a = cells_a[i];
      auto &cell_b = cells_b[i];
      if (cell_a.attr_type() == NULLS && cell_b.attr_type() == NULLS) {
        continue;
      }
      if (cell_a.attr_type() == NULLS) {
        return !order[i];
      }
      if (cell_b.attr_type() == NULLS) {
        return order[i];
      }
      if (cell_a != cell_b) {
        return order[i] ? cell_a > cell_b : cell_a < cell_b;
      }
    }
    return false;  // completely same
  };

  for (size_t i = 0; i < num_threads; ++i) {
    size_t start = i * chunk_size;
    size_t end   = (i == num_threads - 1) ? data.size() : start + chunk_size;

    threads.emplace_back(
        [start, end, &data, &order, &cmp]() { std::sort(data.begin() + start, data.begin() + end, cmp); });
  }

  for (auto &thread : threads) {
    thread.join();
  }
}

void merge_sort(std::vector<CmpPair> &data, size_t num_threads, const bool *order)
{
  size_t chunk_size = data.size() / num_threads;

  auto cmp = [&order](const CmpPair &a, const CmpPair &b) {
    auto &cells_a = a.first;
    auto &cells_b = b.first;
    assert(cells_a.size() == cells_b.size());
    for (size_t i = 0; i < cells_a.size(); ++i) {
      auto &cell_a = cells_a[i];
      auto &cell_b = cells_b[i];
      if (cell_a.attr_type() == NULLS && cell_b.attr_type() == NULLS) {
        continue;
      }
      if (cell_a.attr_type() == NULLS) {
        return !order[i];
      }
      if (cell_b.attr_type() == NULLS) {
        return order[i];
      }
      if (cell_a != cell_b) {
        return order[i] ? cell_a > cell_b : cell_a < cell_b;
      }
    }
    return false;  // completely same
  };

  for (size_t i = chunk_size; i < data.size(); i *= 2) {
    for (size_t j = 0; j < data.size(); j += 2 * i) {
      size_t start  = j;
      size_t middle = j + i;
      size_t end    = std::min(j + 2 * i, data.size());
      std::inplace_merge(data.begin() + start, data.begin() + middle, data.begin() + end, cmp);
    }
  }
}

RC SortPhysicalOperator::fetch_table()
{
  RC rc = RC::SUCCESS;
  // tuple_value_cache_.reserve(81920);
  cache_tuple_ = new CacheTuple(specs_);

  int                  index = 0;
  std::vector<CmpPair> pair_sort_table;

  // 被order by选择属性的值的数组
  // 获得order by的排序单元
  const auto &units = orderby_stmt_->orderby_units();

  while (RC::SUCCESS == (rc = children_[0]->next())) {
    Tuple *current_tuple = children_[0]->current_tuple();

    // 遍历排序单元，获得对应属性的值
    std::vector<Value> pair_value(units.size());
    for (int i = 0; i < units.size(); ++i) {
      Expression *expr = units[i]->expr();
      expr->get_value(*current_tuple, pair_value[i]);
    }
    // 当前tuple需要排序属性的值存储下来
    pair_sort_table.emplace_back(std::make_pair(std::move(pair_value), index++));

    std::vector<Value> data(current_tuple->cell_num());

    for (int i = 0; i < current_tuple->cell_num(); i++) {
      current_tuple->cell_at(i, data[i]);
    }

    tuple_value_cache_.emplace_back(data);
  }

  // 获取到每个排序单元的排序顺序
  bool order[units.size()];
  //  std::vector<bool> order(units.size());
  for (std::vector<OrderByUnit *>::size_type i = 0; i < units.size(); ++i) {
    order[i] = units[i]->sort_type();
  }

  //  const int thread_num = 6;
  //  parallel_sort(pair_sort_table, thread_num, order);
  //  merge_sort(pair_sort_table, thread_num, order);
  auto cmp = [&order](const CmpPair &a, const CmpPair &b) {
    auto &cells_a = a.first;
    auto &cells_b = b.first;
    assert(cells_a.size() == cells_b.size());
    for (size_t i = 0; i < cells_a.size(); ++i) {
      auto &cell_a = cells_a[i];
      auto &cell_b = cells_b[i];
      if (cell_a.attr_type() == NULLS && cell_b.attr_type() == NULLS) {
        continue;
      }
      if (cell_a.attr_type() == NULLS) {
        return !order[i];
      }
      if (cell_b.attr_type() == NULLS) {
        return order[i];
      }
      if (cell_a != cell_b) {
        return order[i] ? cell_a > cell_b : cell_a < cell_b;
      }
    }
    return false;  // completely same
  };
  sort(pair_sort_table.begin(), pair_sort_table.end(), cmp);

  // fill ordered_idx_
  for (size_t i = 0; i < pair_sort_table.size(); ++i) {
    ordered_idx_.emplace_back(pair_sort_table[i].second);
  }
  it_ = -1;

  if (RC::RECORD_EOF == rc) {
    return RC::SUCCESS;
  }
  return rc;
}

RC SortPhysicalOperator::next()
{
  RC rc = RC::SUCCESS;
  // 获取第一条记录的时候就排序，之后直接从存储中拿取
  if (is_first_) {
    is_first_ = false;
    rc        = fetch_table();
    if (RC::SUCCESS != rc) {
      return rc;
    }
  }

  it_++;
  if (it_ < ordered_idx_.size()) {
    return RC::SUCCESS;
  }
  return RC::RECORD_EOF;
}

RC SortPhysicalOperator::close()
{
  RC rc = RC::SUCCESS;
  children_[0]->close();
  return rc;
}

Tuple *SortPhysicalOperator::current_tuple()
{
  if (it_ < ordered_idx_.size()) {
    cache_tuple_->set_record(&tuple_value_cache_[ordered_idx_[it_]]);
    return cache_tuple_;
  }
  return nullptr;
}

void SortPhysicalOperator::add_spec(const Table *table, const FieldMeta *field_meta)
{
  specs_.push_back(new TupleCellSpec(table->name(), field_meta->name(), nullptr));
}