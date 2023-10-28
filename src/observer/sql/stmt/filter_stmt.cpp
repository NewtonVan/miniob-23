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
// Created by Wangyunlai on 2022/5/22.
//

#include "common/rc.h"
#include "common/log/log.h"
#include "common/lang/string.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/db/db.h"
#include "storage/table/table.h"

FilterStmt::~FilterStmt()
{
  for (FilterUnit *unit : filter_units_) {
    delete unit;
  }
  filter_units_.clear();
}

RC FilterStmt::create(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
    const ConditionSqlNode *conditions, int condition_num, FilterStmt *&stmt)
{
  LOG_DEBUG("create filter stmt");
  RC rc = RC::SUCCESS;
  stmt = nullptr;

  FilterStmt *tmp_stmt = new FilterStmt();
  for (int i = 0; i < condition_num; i++) {
    FilterUnit *filter_unit = nullptr;
    rc = create_filter_unit(db, default_table, tables, conditions[i], filter_unit);
    if (rc != RC::SUCCESS) {
      delete tmp_stmt;
      LOG_WARN("failed to create filter unit. condition index=%d", i);
      return rc;
    }
    tmp_stmt->filter_units_.push_back(filter_unit);
  }

  stmt = tmp_stmt;
  return rc;
}

RC get_table_and_field(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
    const RelAttrSqlNode &attr, Table *&table, const FieldMeta *&field)
{
  if (common::is_blank(attr.relation_name.c_str())) {
    table = default_table;
  } else if (nullptr != tables) {
    auto iter = tables->find(attr.relation_name);
    if (iter != tables->end()) {
      table = iter->second;
    }
  } else {
    table = db->find_table(attr.relation_name.c_str());
  }
  if (nullptr == table) {
    LOG_WARN("No such table: attr.relation_name: %s", attr.relation_name.c_str());
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  field = table->table_meta().field(attr.attribute_name.c_str());
  if (nullptr == field) {
    LOG_WARN("no such field in table: table %s, field %s", table->name(), attr.attribute_name.c_str());
    table = nullptr;
    return RC::SCHEMA_FIELD_NOT_EXIST;
  }

  return RC::SUCCESS;
}

RC FilterStmt::create_filter_unit(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
    const ConditionSqlNode &condition, FilterUnit *&filter_unit)
{
  LOG_DEBUG("create filter unit");
  LOG_DEBUG("left_is_attr: %d, right_is_attr: %d", condition.left_is_attr, condition.right_is_attr);
  LOG_DEBUG("condition.left_value.attr_type(): %d, condition.right_value.attr_type(): %d", condition.left_value.attr_type(), condition.right_value.attr_type());
  LOG_DEBUG("condition.left_value.data(): %s, condition.right_value.data(): %s", condition.left_value.data(), condition.right_value.data());

  RC rc = RC::SUCCESS;

  CompOp comp = condition.comp;
  if (comp < EQUAL_TO || comp >= NO_OP) {
    LOG_WARN("invalid compare operator : %d", comp);
    return RC::INVALID_ARGUMENT;
  }

  filter_unit = new FilterUnit;
  AttrType lefr_attr_name;
  if (condition.left_is_attr) {
    LOG_DEBUG("condition.left_is_attr");
    Table *table = nullptr;
    const FieldMeta *field = nullptr;
    rc = get_table_and_field(db, default_table, tables, condition.left_attr, table, field);
    if (rc != RC::SUCCESS) {
      LOG_WARN("cannot find attr");
      return rc;
    }
    FilterObj filter_obj;
    filter_obj.init_attr(Field(table, field));
    filter_unit->set_left(filter_obj);
    lefr_attr_name = default_table->table_meta().field(condition.left_attr.attribute_name.c_str())->type();
  } else {
    LOG_DEBUG("FilterObj filter_obj");
    FilterObj filter_obj;
    filter_obj.init_value(condition.left_value);
    filter_unit->set_left(filter_obj);
  }

  AttrType right_attr_name;
  if (condition.right_is_attr) {
    LOG_DEBUG("condition.right_is_attr");
    Table *table = nullptr;
    const FieldMeta *field = nullptr;
    rc = get_table_and_field(db, default_table, tables, condition.right_attr, table, field);
    if (rc != RC::SUCCESS) {
      LOG_WARN("cannot find attr");
      return rc;
    }
    FilterObj filter_obj;
    filter_obj.init_attr(Field(table, field));
    filter_unit->set_right(filter_obj);
    right_attr_name = default_table->table_meta().field(condition.right_attr.attribute_name.c_str())->type();
  } else {
    LOG_DEBUG("filter_obj.init_value(condition.right_value)");
    FilterObj filter_obj;
    filter_obj.init_value(condition.right_value);
    filter_unit->set_right(filter_obj);
  }

  LOG_DEBUG("filter_unit->left().value.attr_type(): %d, filter_unit->right().value.attr_type(): %d", filter_unit->left().value.attr_type(), filter_unit->right().value.attr_type());
  LOG_DEBUG("filter_unit->left().value.data(): %s, filter_unit->right().value.data(): %s", filter_unit->left().value.data(), filter_unit->right().value.data());
  if(lefr_attr_name == DATES && filter_unit->right().value.attr_type() == CHARS) {
    int64_t date;
    bool valid = serialize_date(&date, filter_unit->right().value.data());
    if (!valid) {
      LOG_DEBUG("invalid date: %s", filter_unit->right().value.data());
      return RC::INVALID_ARGUMENT;
    } else {
      filter_unit->right().value.set_type(DATES);
      filter_unit->right().value.set_date(date);
    }
  } else if(right_attr_name == DATES && filter_unit->left().value.attr_type() == CHARS) {
    int64_t date;
    bool valid = serialize_date(&date, filter_unit->left().value.data());
    if (!valid) {
      LOG_DEBUG("invalid date: %s", filter_unit->left().value.data());
      return RC::INVALID_ARGUMENT;
    } else {
      filter_unit->left().value.set_type(DATES);
      filter_unit->left().value.set_date(date);
    }
  }

  if(lefr_attr_name == TEXTS && filter_unit->right().value.attr_type() == CHARS) {
    filter_unit->right().value.set_type(TEXTS);
    filter_unit->right().value.set_text(filter_unit->right().value.data());
  } else if(right_attr_name == TEXTS && filter_unit->left().value.attr_type() == CHARS) {
    filter_unit->left().value.set_type(TEXTS);
    filter_unit->left().value.set_text(filter_unit->left().value.data());
  }

//  if(lefr_attr_name != filter_unit->right().value.attr_type() && condition.comp != IS_LEFT_NOT_NULL && condition.comp != IS_LEFT_NULL && lefr_attr_name != NULLS) {
//    return RC::SCHEMA_FIELD_TYPE_MISMATCH;
//  }

  filter_unit->set_comp(comp);

  // 检查两个类型是否能够比较
  return rc;
}
