//
// Created by hyq on 11/5/23.
//

#include "sql/operator/insert_create_select_physical_operator.h"
#include "sql/operator/project_physical_operator.h"
#include "sql/stmt/insert_stmt.h"
#include "storage/table/table.h"
#include "storage/trx/trx.h"

using namespace std;

std::string extractFieldName(const std::string& input) {
  if(input.find(')') < input.size()) {
    return input;
  }
  size_t dotPosition = input.find('.');

  if (dotPosition != std::string::npos && dotPosition < input.length() - 1) {
    return input.substr(dotPosition + 1);
  }

  return input;
}

RC InsertCreateSelectPhysicalOperator::open(Trx *trx)
{
  if (children_.empty()) {
    return RC::SUCCESS;
  }

  PhysicalOperator *child = children_[0].get();
  RC                rc    = child->open(trx);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }

  trx_ = trx;
  return RC::SUCCESS;
}

RC InsertCreateSelectPhysicalOperator::next()
{
  ProjectPhysicalOperator* projectOp = static_cast<ProjectPhysicalOperator*>(children_[0].get());
  int left_not_in_right_count = 0;

  // 创建表
  std::vector<AttrInfoSqlNode> new_attr_infos;
  if(!projectOp->expressions().empty()) {
    build_attrs_for_exprs(new_attr_infos, left_not_in_right_count);
  } else {
    build_attrs_for_fields(new_attr_infos, left_not_in_right_count);
  }

  if (children_.empty()) {
    return RC::RECORD_EOF;
  }

  RC rc = RC::SUCCESS;
  // 一次全部取出
  std::vector<std::vector<Value>> all_values;
  // 记录char类型字段的最大长度
  int max_char_length = 0;
  while(RC::SUCCESS == (rc = children_[0]->next())) {
    std::vector<Value> values;
    for(int i = 0; i < left_not_in_right_count; i++) {
      Value value;
      value.set_type(NULLS);
      values.emplace_back(std::move(value));
    }

    Tuple    *tuple    = children_[0]->current_tuple();
    const int cell_num = tuple->cell_num();
    Value     cell;
    for (int i = 0; i < cell_num; ++i) {
      if (tuple->cell_at(i, cell) != RC::SUCCESS) {
        return RC::RECORD_EOF;
      }
      values.push_back(cell);
      if(cell.attr_type() == CHARS) {
        max_char_length = max(max_char_length, cell.length());
      }
    }
    all_values.push_back(std::move(values));
  }

  for(int i = 0; i < all_values.size(); i++) {
    if(i == 0) {
      for(int j = 0; j < all_values[i].size(); j++) {
        if(all_values[i][j].attr_type() == CHARS) {
          new_attr_infos[j].length = max_char_length;
        }
        new_attr_infos[j].type = all_values[i][j].attr_type();
      }
      create_table(new_attr_infos);
    }

    Record record;
    rc = insert_record(std::move(all_values[i]));
    if(rc != RC::SUCCESS) {
      return rc;
    }
  }

  return RC::RECORD_EOF;
}

void InsertCreateSelectPhysicalOperator::build_attrs_for_exprs(std::vector<AttrInfoSqlNode>& new_attr_infos, int& left_not_in_right_count) {
  ProjectPhysicalOperator* projectOp = static_cast<ProjectPhysicalOperator*>(children_[0].get());

  for(const auto& attr_info : table_select_attr_infos_) {
    bool find = false;
    for(const auto& expr : projectOp->expressions()) {
      if(attr_info.name == extractFieldName(expr->name())) {
        find = true;
        break;
      }
    }
    if(!find) {
      new_attr_infos.push_back(attr_info);
      left_not_in_right_count++;
    }
  }

  AttrInfoSqlNode attr;
  for(const auto& expr : projectOp->expressions()) {
    Value value;
    RC rc = expr->try_get_value(value);
    if(rc == RC::SUCCESS) {
      attr.type = value.attr_type();
      attr.length = value.length();
    } else {
      attr.type = expr->value_type();
      attr.length = 4;
    }
    attr.name = extractFieldName(expr->name());
    attr.null = true;

    new_attr_infos.push_back(attr);
  }
}

void InsertCreateSelectPhysicalOperator::build_attrs_for_fields(std::vector<AttrInfoSqlNode>& new_attr_infos, int& left_not_in_right_count) {
  for(const auto& attr_info : table_select_attr_infos_) {
    bool find = false;
    for(const auto& field : fields_) {
      if(attr_info.name == extractFieldName(field.meta()->name())) {
        find = true;
        break;
      }
    }
    if(!find) {
      new_attr_infos.push_back(attr_info);
      left_not_in_right_count++;
    }
  }

  AttrInfoSqlNode attr;
  for(const auto& field : fields_) {
    attr.name = extractFieldName(field.meta()->name());
    attr.length = field.meta()->len();
    attr.null = field.meta()->nullable();
    attr.type = field.meta()->type();
    new_attr_infos.push_back(attr);
  }
}

void InsertCreateSelectPhysicalOperator::create_table(std::vector<AttrInfoSqlNode>& new_attr_infos) {
  db_->create_table(table_name_.c_str(), new_attr_infos.size(), new_attr_infos.data());
  table_ = db_->find_table(table_name_.c_str());
}

RC InsertCreateSelectPhysicalOperator::insert_record(std::vector<Value>&& values) {
  Record record;
  RC rc = table_->make_record(static_cast<int>(values.size()), values.data(), record);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to make record. rc=%s", strrc(rc));
    return rc;
  }

  rc = trx_->insert_record(table_, record);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to insert record by transaction. rc=%s", strrc(rc));
  }
  return rc;
}

RC InsertCreateSelectPhysicalOperator::close()
{
  return RC::SUCCESS;
}