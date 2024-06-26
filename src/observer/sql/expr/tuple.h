/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2021/5/14.
//

#pragma once

#include <bits/types/FILE.h>
#include <cstddef>
#include <cstring>
#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>
#include <string>

#include "common/log/log.h"
#include "sql/expr/tuple_cell.h"
#include "sql/parser/parse.h"
#include "sql/parser/parse_defs.h"
#include "common/hash_util.h"
#include "sql/parser/value.h"
#include "sql/expr/expression.h"
#include "storage/record/record.h"

class Table;

/**
 * @defgroup Tuple
 * @brief Tuple 元组，表示一行数据，当前返回客户端时使用
 * @details
 * tuple是一种可以嵌套的数据结构。
 * 比如select t1.a+t2.b from t1, t2;
 * 需要使用下面的结构表示：
 * @code {.cpp}
 *  Project(t1.a+t2.b)
 *        |
 *      Joined
 *      /     \
 *   Row(t1) Row(t2)
 * @endcode
 *
 */

/**
 * @brief 元组的结构，包含哪些字段(这里成为Cell)，每个字段的说明
 * @ingroup Tuple
 */
class TupleSchema
{
public:
  void                 append_cell(const TupleCellSpec &cell) { cells_.push_back(cell); }
  void                 append_cell(const char *table, const char *field) { append_cell(TupleCellSpec(table, field)); }
  void                 append_cell(const char *alias) { append_cell(TupleCellSpec(alias)); }
  int                  cell_num() const { return static_cast<int>(cells_.size()); }
  const TupleCellSpec &cell_at(int i) const { return cells_[i]; }

private:
  std::vector<TupleCellSpec> cells_;
};


enum TupleType {
  UNKNOWN,
  ROW,
  PROJECT,
  EXPR,
  VALUELIST,
  JOIN,
  SORT,
  AGG,
  CACHE,
};

/**
 * @brief 元组的抽象描述
 * @ingroup Tuple
 */
class Tuple
{
public:
  Tuple()          = default;
  virtual ~Tuple() = default;

  /**
   * @brief 获取元组中的Cell的个数
   * @details 个数应该与tuple_schema一致
   */
  virtual int cell_num() const = 0;

  /**
   * @brief 获取指定位置的Cell
   *
   * @param index 位置
   * @param[out] cell  返回的Cell
   */
  virtual RC cell_at(int index, Value &cell) const = 0;

  /**
   * @brief 根据cell的描述，获取cell的值
   *
   * @param spec cell的描述
   * @param[out] cell 返回的cell
   */
  virtual RC find_cell(const TupleCellSpec &spec, Value &cell) const = 0;

  virtual std::string to_string() const
  {
    std::string str;
    // 获取tuple中字段的个数
    const int cell_num = this->cell_num();
    for (int i = 0; i < cell_num - 1; i++) {
      Value cell;
      // 获得字段0的值
      cell_at(i, cell);
      // 将字段0的值转换为字符串
      str += cell.to_string();
      str += ", ";
    }

    if (cell_num > 0) {
      Value cell;
      cell_at(cell_num - 1, cell);
      str += cell.to_string();
    }
    return str;
  }
  virtual TupleType type() const = 0;
  virtual std::vector<TupleCellSpec *> get_row_schema() const { return std::vector<TupleCellSpec *>(); }
};

class CacheTuple : public Tuple
{
public:
  CacheTuple(const std::vector<TupleCellSpec *> &speces) : speces_(speces) {}
  virtual ~CacheTuple()
  {
    // for (TupleCellSpec *spec : speces_) {
    //   delete spec;
    // }
    // speces_.clear();
  }

  void set_record(std::vector<Value> *values) { this->values_ = values; }

  void set_schema(std::vector<TupleCellSpec *> &speces) { speces_ = speces; }

  int cell_num() const override { return speces_.size(); }

  RC cell_at(int index, Value &cell) const override
  {
    if (index < 0 || index >= static_cast<int>(speces_.size())) {
      LOG_WARN("invalid argument. index=%d", index);
      return RC::INVALID_ARGUMENT;
    }

    cell.set_type((*values_)[index].attr_type());
    cell.set_data((*values_)[index].data(), (*values_)[index].length());
    return RC::SUCCESS;
  }

  RC find_cell(const TupleCellSpec &spec, Value &cell) const override
  {
    if (speces_.empty()) {
      LOG_WARN("invalid argument. empty schema");
      return RC::INTERNAL;
    }
    if (spec.alias() != nullptr) {
      for (size_t i = 0; i < speces_.size(); ++i) {
        if (speces_[i]->alias() != nullptr && 0 == strcmp(spec.alias(), speces_[i]->alias())) {
          return cell_at(i, cell);
        }
      }
    }

    for (int i = 0; i < speces_.size(); ++i) {
      if (0 == strcmp(spec.table_name(), speces_[i]->table_name()) &&
          0 == strcmp(spec.field_name(), speces_[i]->field_name())) {
        return cell_at(i, cell);
      }
    }
    return RC::NOTFOUND;
  }

  std::vector<TupleCellSpec *> get_row_schema() const override { return speces_; }

  TupleType type() const override { return TupleType::CACHE; }

private:
  std::vector<Value>          *values_;
  std::vector<TupleCellSpec *> speces_;
};

/**
 * @brief 一行数据的元组
 * @ingroup Tuple
 * @details 直接就是获取表中的一条记录
 */
class RowTuple : public Tuple
{
public:
  RowTuple() = default;
  virtual ~RowTuple()
  {
    for (FieldExpr *spec : speces_) {
      delete spec;
    }
    speces_.clear();
  }

  void set_record(Record *record) { this->record_ = record; }

  void set_schema(const Table *table, const std::vector<FieldMeta> *fields)
  {
    table_ = table;
    this->speces_.reserve(fields->size());
    for (const FieldMeta &field : *fields) {
      speces_.push_back(new FieldExpr(table, &field));
    }
  }

  int cell_num() const override { return speces_.size(); }

  RC cell_at(int index, Value &cell) const override
  {
    if (index < 0 || index >= static_cast<int>(speces_.size())) {
      LOG_WARN("invalid argument. index=%d", index);
      return RC::INVALID_ARGUMENT;
    }

    FieldExpr       *field_expr             = speces_[index];
    const FieldMeta *field_meta             = field_expr->field().meta();
    int              null_mask_field_offset = table_->table_meta().null_mask_field()->offset();
    int              null_mask              = *(int *)(this->record_->data() + null_mask_field_offset) & 0x00FFFFFFFF;
    // 判断这个字段是否为空
    if (null_mask >> index & 1) {
      cell.set_type(NULLS);
      return RC::SUCCESS;
    }
    cell.set_type(field_meta->type());
    cell.set_data(this->record_->data() + field_meta->offset(), field_meta->len());
    return RC::SUCCESS;
  }

  RC find_cell(const TupleCellSpec &spec, Value &cell) const override
  {
    const char *table_name = spec.table_name();
    const char *field_name = spec.field_name();
    if (0 != strcmp(table_name, table_->name())) {
      return RC::NOTFOUND;
    }

    for (size_t i = 0; i < speces_.size(); ++i) {
      const FieldExpr *field_expr = speces_[i];
      const Field     &field      = field_expr->field();
      if (0 == strcmp(field_name, field.field_name())) {
        return cell_at(i, cell);
      }
    }
    return RC::NOTFOUND;
  }
  TupleType type() const override {
    return TupleType::ROW;
  }

  std::vector<TupleCellSpec *> get_row_schema() const override
  {
    const int                    speces_size = speces_.size();
    std::vector<TupleCellSpec *> speces(speces_size);

    for (int i = 0; i < speces_size; ++i) {
      bool null_alias = nullptr == speces_[i]->field_alias() || strlen(speces_[i]->field_alias()) == 0;
      speces[i] =
          new TupleCellSpec(table_->name(), speces_[i]->field_name(), null_alias ? nullptr : speces_[i]->field_alias());
    }

    return speces;
  }

#if 0
  RC cell_spec_at(int index, const TupleCellSpec *&spec) const override
  {
    if (index < 0 || index >= static_cast<int>(speces_.size())) {
      LOG_WARN("invalid argument. index=%d", index);
      return RC::INVALID_ARGUMENT;
    }
    spec = speces_[index];
    return RC::SUCCESS;
  }
#endif

  Record &record() { return *record_; }

  const Record &record() const { return *record_; }

private:
  Record                  *record_ = nullptr;
  const Table             *table_  = nullptr;
  std::vector<FieldExpr *> speces_;
};

/**
 * @brief 从一行数据中，选择部分字段组成的元组，也就是投影操作
 * @ingroup Tuple
 * @details 一般在select语句中使用。
 * 投影也可以是很复杂的操作，比如某些字段需要做类型转换、重命名、表达式运算、函数计算等。
 * 当前的实现是比较简单的，只是选择部分字段，不做任何其他操作。
 */
class ProjectTuple : public Tuple
{
public:
  ProjectTuple() = default;
  virtual ~ProjectTuple()
  {
    for (TupleCellSpec *spec : speces_) {
      delete spec;
    }
    speces_.clear();
  }

  void set_tuple(Tuple *tuple) { this->tuple_ = tuple; }

  void add_cell_spec(TupleCellSpec *spec) { speces_.push_back(spec); }
  int  cell_num() const override { return speces_.size(); }

  //id, col
  // 0, 1

  RC cell_at(int index, Value &cell) const override
  {
    if (index < 0 || index >= static_cast<int>(speces_.size())) {
      return RC::INTERNAL;
    }
    if (tuple_ == nullptr) {
      return RC::INTERNAL;
    }

    const TupleCellSpec *spec = speces_[index];
    return tuple_->find_cell(*spec, cell);
  }

  RC find_cell(const TupleCellSpec &spec, Value &cell) const override { return tuple_->find_cell(spec, cell); }
  TupleType type() const override {
    return TupleType::PROJECT;
  }

#if 0
  RC cell_spec_at(int index, const TupleCellSpec *&spec) const override
  {
    if (index < 0 || index >= static_cast<int>(speces_.size())) {
      return RC::NOTFOUND;
    }
    spec = speces_[index];
    return RC::SUCCESS;
  }
#endif
private:
  std::vector<TupleCellSpec *> speces_;
  Tuple                       *tuple_ = nullptr;
};

class ExpressionTuple : public Tuple
{
public:
  ExpressionTuple(std::vector<std::unique_ptr<Expression>> &expressions) : expressions_(expressions) {}

  virtual ~ExpressionTuple()
  {
    if (tuple_ != nullptr) {
      delete tuple_;
    }
  }

  int cell_num() const override { return expressions_.size(); }

  RC cell_at(int index, Value &cell) const override
  {
    if (index < 0 || index >= static_cast<int>(expressions_.size())) {
      return RC::INTERNAL;
    }

    const Expression *expr = expressions_[index].get();

    if (tuple_ != nullptr) {
      return expr->get_value(*tuple_, cell);
    }
    return expr->try_get_value(cell);
  }

  RC find_cell(const TupleCellSpec &spec, Value &cell) const override
  {
    for (const std::unique_ptr<Expression> &expr : expressions_) {
      if (0 == strcmp(spec.alias(), expr->name().c_str())) {
        if (tuple_ != nullptr) {
          return expr->get_value(*tuple_, cell);
        }
        return expr->try_get_value(cell);
      }
    }
    return RC::NOTFOUND;
  }

  void set_tuple(Tuple *tuple) { tuple_ = tuple; }
  TupleType type() const override {
    return TupleType::EXPR;
  }

private:
  const std::vector<std::unique_ptr<Expression>> &expressions_;
  Tuple                                          *tuple_;
};

/**
 * @brief 一些常量值组成的Tuple
 * @ingroup Tuple
 */
class ValueListTuple : public Tuple
{
public:
  ValueListTuple()          = default;
  virtual ~ValueListTuple() = default;

  void set_cells(const std::vector<Value> &cells) { cells_ = cells; }

  virtual int cell_num() const override { return static_cast<int>(cells_.size()); }

  virtual RC cell_at(int index, Value &cell) const override
  {
    if (index < 0 || index >= cell_num()) {
      return RC::NOTFOUND;
    }

    cell = cells_[index];
    return RC::SUCCESS;
  }

  virtual RC find_cell(const TupleCellSpec &spec, Value &cell) const override { return RC::INTERNAL; }

  TupleType type() const override {
    return TupleType::VALUELIST;
  }

private:
  std::vector<Value> cells_;
};

/**
 * @brief 将两个tuple合并为一个tuple
 * @ingroup Tuple
 * @details 在join算子中使用
 */
class JoinedTuple : public Tuple
{
public:
  JoinedTuple()          = default;
  virtual ~JoinedTuple() = default;

  void set_left(Tuple *left) { left_ = left; }
  void set_right(Tuple *right) { right_ = right; }

  int cell_num() const override { return left_->cell_num() + right_->cell_num(); }

  RC cell_at(int index, Value &value) const override
  {
    const int left_cell_num = left_->cell_num();
    if (index > 0 && index < left_cell_num) {  // >= 0 ?
      return left_->cell_at(index, value);
    }

    if (index >= left_cell_num && index < left_cell_num + right_->cell_num()) {
      return right_->cell_at(index - left_cell_num, value);
    }

    return RC::NOTFOUND;
  }

  RC find_cell(const TupleCellSpec &spec, Value &value) const override
  {
    RC rc = left_->find_cell(spec, value);
    if (rc == RC::SUCCESS || rc != RC::NOTFOUND) {
      return rc;
    }

    return right_->find_cell(spec, value);
  }

  TupleType type() const override {
    return TupleType::JOIN;
  }
  std::vector<TupleCellSpec *> get_row_schema() const override
  {
    std::vector<TupleCellSpec *> speces;
    if (left_ != nullptr) {
      std::vector<TupleCellSpec *> left_schema(left_->get_row_schema());
      speces.insert(speces.end(), left_schema.begin(), left_schema.end());
    }
    if (right_ != nullptr) {
      std::vector<TupleCellSpec *> right_schema(right_->get_row_schema());
      speces.insert(speces.end(), right_schema.begin(), right_schema.end());
    }

    return speces;
  }

private:
  Tuple *left_  = nullptr;
  Tuple *right_ = nullptr;
};

class SortTuple : public Tuple
{
public:
  SortTuple() = default;
  //  SortTuple(const SortTuple&) = delete;
  SortTuple(SortTuple &&) = default;  // 默认生成移动构造函数

  void set_tuple(std::vector<Value> &values, std::vector<TupleCellSpec> *specs)
  {
    values_ = std::move(values);  // 使用移动语义避免不必要的拷贝
    specs_  = specs;              // 使用移动语义避免不必要的拷贝
  }

  virtual ~SortTuple() = default;

  int cell_num() const override { return values_.size(); }

  RC cell_at(int index, Value &value) const override
  {
    const int left_cell_num = cell_num();
    if (index > 0 && index < cell_num()) {
      value = values_[index];
      return RC::SUCCESS;
    }
    return RC::NOTFOUND;
  }

  RC find_cell(const TupleCellSpec &spec, Value &value) const override
  {
    for (size_t i = 0; i < specs_->size(); ++i) {
      if (0 == strcmp(spec.table_name(), specs_->at(i).table_name()) &&
          0 == strcmp(spec.field_name(), specs_->at(i).field_name()) &&
          0 == strcmp(spec.alias(), specs_->at(i).alias())) {
        return cell_at(i, value);
      }
    }
    return RC::NOTFOUND;
  }
  TupleType type() const override {
    return TupleType::SORT;
  }

private:
  std::vector<TupleCellSpec> *specs_;
  std::vector<Value>          values_;
};

/** AggregateKey represents a key in an aggregation operation */
struct AggregationKey
{
  /** The group-by values */
  std::vector<Value> group_bys_;

  /**
   * Compares two aggregate keys for equality.
   * @param other the other aggregate key to be compared with
   * @return `true` if both aggregate keys have equivalent group-by expressions, `false` otherwise
   */
  auto operator==(const AggregationKey &other) const -> bool
  {
    for (uint32_t i = 0; i < other.group_bys_.size(); i++) {
      if (group_bys_[i].compare(other.group_bys_[i]) != 0) {
        return false;
      }
    }
    return true;
  }
};

namespace std {

/** Implements std::hash on AggregateKey */
template <>
struct hash<AggregationKey>
{
  auto operator()(const AggregationKey &agg_key) const -> std::size_t
  {
    size_t curr_hash = 0;
    for (const auto &key : agg_key.group_bys_) {
      if (!key.is_null()) {
        curr_hash = MyHash::HashUtil::CombineHashes(curr_hash, MyHash::HashUtil::HashValue(&key));
      }
    }
    return curr_hash;
  }
};

}  // namespace std

struct AggregationValue
{
  std::vector<Value>  aggregates;
  std::vector<size_t> not_null_count_;
};

class AggTuple : public Tuple {
  public:
    void set_tuple(std::vector<Value>& tuple, std::vector<TupleCellSpec>& agg_specs, std::vector<TupleCellSpec>& group_by_spec) {
      tuple_ = tuple;
      agg_specs_ = agg_specs;
      groub_by_specs_ = group_by_spec;
    }

    int cell_num() const override
    {
      return tuple_.size();
    }

  RC cell_at(int index, Value &value) const override // fix
  {
    // const int left_cell_num =cell_num();
    if (index >= 0 && index < cell_num()) {
      value = tuple_[index];
      return RC::SUCCESS;
    }

    return RC::NOTFOUND;
  }

  // AggExpr eval on AggTuple by alias
  RC find_cell(const TupleCellSpec &spec, Value &value) const override
  {
    // find in agg field
    for (size_t i = 0; i < agg_specs_.size(); ++i) {
      // check alias for now
      // alias check for agg call, like count(*)
      // table name and relation name check for group by
      if (0 == strcmp(spec.alias(), agg_specs_[i].alias())) {
        return cell_at(i, value);
      }
    }

    // find in group by field
    for (size_t i = 0; i < groub_by_specs_.size(); ++i) {
      // check alias for now
      // alias check for agg call, like count(*)
      // table name and relation name check for group by
      if (0 == strcmp(spec.table_name(), groub_by_specs_[i].table_name()) && 0 == strcmp(spec.field_name(), groub_by_specs_[i].field_name())) {
        return cell_at(i + agg_specs_.size() , value);
      }
    }

    return RC::NOTFOUND;
  }

  TupleType type() const override {
    return TupleType::AGG;
  }


  private:
    // agg field and group_by field
    // exmaple: select count(*) from aggregation_func group by name
    //  name   course
    //. smith.   1
    //. smith    2
    // ....
    //  bob      1
    // ...

    // {value(2), value("smith")}
    // agg field first, then group by field
    // agg field is accessed by alias, i.e. expr name "count(*)"
    // group by field accessed by relation name and field name
    std::vector<Value> tuple_;
    std::vector<TupleCellSpec> agg_specs_;
    std::vector<TupleCellSpec> groub_by_specs_;
};

// agg hash table
class SimpleHashTable
{
public:
  SimpleHashTable(std::vector<AggType> &agg_types) : agg_types_(agg_types){};
  ~SimpleHashTable() = default;

  int size() const { return agg_types_.size(); }

  AggregationValue gen_base_aggregates()
  {
    AggregationValue agg_value;
    for (int i = 0; i < agg_types_.size(); i++) {
      switch (agg_types_[i]) {
      case COUNT_STAR:
        agg_value.aggregates.push_back(Value::get_null(AttrType::INTS));
        agg_value.not_null_count_.push_back(0);
        break;
      case COUNT_AGG:
        agg_value.aggregates.push_back(Value::get_null(AttrType::INTS));
        agg_value.not_null_count_.push_back(0);
        break;
      case SUM_AGG:
      case MIN_AGG:
      case MAX_AGG:
      case AVG_AGG:
      // deal with float conversion in CombineAggregateValues
        Value val;
        val.set_type(AttrType::NULLS);
        agg_value.aggregates.push_back(val);
        agg_value.not_null_count_.push_back(0);
        break;
      }
    }
    return agg_value;
  }

  void CombineAggregateValues(AggregationValue *result, const AggregationValue &input) {
    for (uint32_t i = 0; i < agg_types_.size(); i++) {
      Value &agg_val = result->aggregates[i];
      if (!input.aggregates[i].is_null()) {
        result->not_null_count_[i]++;
      }
      switch (agg_types_[i]) {
        case AggType::COUNT_STAR: agg_val.set_int(agg_val.get_int() + 1); break;
        case AggType::COUNT_AGG:
          if (!input.aggregates[i].is_null()) {
            agg_val.set_int(agg_val.get_int() + 1);
          }
          break;
        case AggType::SUM_AGG:
        case AggType::AVG_AGG:  // calc avg when agg executor down
          if (!input.aggregates[i].is_null()) {
            if (agg_val.is_null()) {
              agg_val = input.aggregates[i];
            } else {
              ASSERT(agg_val.attr_type() == input.aggregates[i].attr_type(), "sum agg on different type");
              switch (agg_val.attr_type()) {
                case AttrType::INTS: agg_val.set_int(agg_val.get_int() + input.aggregates[i].get_int()); break;
                case AttrType::FLOATS: agg_val.set_float(agg_val.get_float() + input.aggregates[i].get_float()); break;
                default: LOG_ERROR("sum on type%d and type%d", agg_val.attr_type(), input.aggregates[i].attr_type());
              }
            }
          }
          break;
        case AggType::MAX_AGG:
          if (!input.aggregates[i].is_null()) {
            if (agg_val.is_null()) {
              agg_val = input.aggregates[i];
            } else {
              ASSERT(agg_val.attr_type() == input.aggregates[i].attr_type(), "sum agg on different type");
              switch (agg_val.attr_type()) {
                case AttrType::INTS:
                  if (agg_val.get_int() < input.aggregates[i].get_int()) {
                    agg_val = input.aggregates[i];
                  }
                  break;
                case AttrType::FLOATS:
                  if (agg_val.get_float() < input.aggregates[i].get_float()) {
                    agg_val = input.aggregates[i];
                  }
                  break;
                case AttrType::DATES:
                  if (agg_val.get_date() < input.aggregates[i].get_float()) {
                    agg_val = input.aggregates[i];
                  }
                  break;
                case AttrType::CHARS:  // fix agg min/max on char is legal
                  if (agg_val.get_string() < input.aggregates[i].get_string()) {
                    agg_val = input.aggregates[i];
                  }
                  break;

                default: LOG_ERROR("agg max on type%d", agg_val.attr_type());
              }
            }
          }
          break;
        case AggType::MIN_AGG:
          if (!input.aggregates[i].is_null()) {
            if (agg_val.is_null()) {
              agg_val = input.aggregates[i];
            } else {
              ASSERT(agg_val.attr_type() == input.aggregates[i].attr_type(), "sum agg on different type");
              switch (agg_val.attr_type()) {
                case AttrType::INTS:
                  if (agg_val.get_int() > input.aggregates[i].get_int()) {
                    agg_val = input.aggregates[i];
                  }
                  break;
                case AttrType::FLOATS:
                  if (agg_val.get_float() > input.aggregates[i].get_float()) {
                    agg_val = input.aggregates[i];
                  }
                  break;
                case AttrType::DATES:
                  if (agg_val.get_date() > input.aggregates[i].get_date()) {
                    agg_val = input.aggregates[i];
                  }
                  break;

                case AttrType::CHARS:  // fix agg min/max on char is legal
                  if (agg_val.get_string() > input.aggregates[i].get_string()) {
                    agg_val = input.aggregates[i];
                  }
                  break;
                default: LOG_ERROR("agg min on type%d", agg_val.attr_type());
              }
            }
          }
          break;
      }
    }
  }

  /**
   * Inserts a value into the hash table and then combines it with the current aggregation.
   * @param agg_key the key to be inserted
   * @param agg_val the value to be inserted
   */
  void InsertCombine(const AggregationKey &agg_key, const AggregationValue &agg_val)
  {
    if (ht_.count(agg_key) == 0) {
      ht_.insert({agg_key, gen_base_aggregates()});
    }
    CombineAggregateValues(&ht_[agg_key], agg_val);
  }

  /**
   * Clear the hash table
   */
  void Clear() { ht_.clear(); }

  /** An iterator over the aggregation hash table */
  class Iterator
  {
  public:
    /** Creates an iterator for the aggregate map. */
    explicit Iterator(std::unordered_map<AggregationKey, AggregationValue>::iterator iter) : iter_{iter} {}

    /** @return The key of the iterator */
    auto Key() -> const AggregationKey & { return iter_->first; }

    /** @return The value of the iterator */
    auto Val() const -> const AggregationValue & { return iter_->second; }

    auto Val() -> AggregationValue & { return iter_->second; }

    /** @return The iterator before it is incremented */
    auto operator++() -> Iterator &
    {
      ++iter_;
      return *this;
    }

    /** @return `true` if both iterators are identical */
    auto operator==(const Iterator &other) -> bool { return this->iter_ == other.iter_; }

    /** @return `true` if both iterators are different */
    auto operator!=(const Iterator &other) -> bool { return this->iter_ != other.iter_; }

  private:
    /** Aggregates map */
    std::unordered_map<AggregationKey, AggregationValue>::iterator iter_;
  };

  /** @return Iterator to the start of the hash table */
  auto Begin() -> Iterator { return Iterator{ht_.begin()}; }

  /** @return Iterator to the end of the hash table */
  auto End() -> Iterator { return Iterator{ht_.end()}; }

private:
  //
  // funcs[i] exec on cell_specs[i]
  std::vector<AggType> agg_types_;

  // todo(lyq)
  // without group_by, we only need one AggregationValue
  // we suppose the key for it is fix number "1"
  std::unordered_map<AggregationKey, AggregationValue> ht_;
};
