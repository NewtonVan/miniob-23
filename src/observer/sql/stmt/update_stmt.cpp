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

#include "sql/stmt/update_stmt.h"
#include "sql/parser/value.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/db/db.h"
#include "storage/field/field_meta.h"
#include "storage/table/table_meta.h"
#include <string>
#include <vector>

UpdateStmt::UpdateStmt(Table *table, std::vector<Value> &values, int value_amount, FilterStmt *filter_stmt,
    std::vector<std::string> &attribute_name)
    : table_(table),
      values_(values),
      value_amount_(value_amount),
      filter_stmt_(filter_stmt),
      attribute_names_(attribute_name)
{}

UpdateStmt::~UpdateStmt()
{
  if (nullptr != filter_stmt_) {
    delete filter_stmt_;
    filter_stmt_ = nullptr;
  }
}

RC UpdateStmt::create(Db *db, const UpdateSqlNode &update, Stmt *&stmt)
{
  const char *table_name = update.relation_name.c_str();
  if (nullptr == db || nullptr == table_name) {
    LOG_WARN("invalid argument. db=%p, table_name=%p", db, table_name);
    return RC::INVALID_ARGUMENT;
  }

  // check whether the table exists
  Table *table = db->find_table(table_name);
  if (nullptr == table) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  const int                update_fields_cnt = update.update_units.size();
  std::vector<std::string> attributes;
  std::vector<Value>       values;
  for (int i = 0; i < update_fields_cnt; ++i) {
    // check whether field match
    const TableMeta &table_meta = table->table_meta();
    const FieldMeta *field_meta = table_meta.field(update.update_units[i].attribute_name.c_str());
    if (nullptr == field_meta) {
      LOG_WARN("no such field. table_name=%s, field=%s", table_name, update.update_units[i].attribute_name.c_str());
      return RC::SCHEMA_FIELD_NOT_EXIST;
    }

    // convert data type if needed
    const AttrType field_type   = field_meta->type();
    const AttrType value_type   = update.update_units[i].value.attr_type();
    Value         *mutableValue = const_cast<Value *>(&update.update_units[i].value);
    if(!field_meta->nullable() && value_type == NULLS) return RC::INVALID_ARGUMENT;
    if(field_meta->nullable() && value_type == NULLS) continue;
    if (field_type != value_type) {
      if (field_type == AttrType::DATES && value_type == AttrType::CHARS) {
        int64_t date;
        bool    valid = serialize_date(&date, mutableValue->data());
        if (!valid) {
          return RC::INVALID_ARGUMENT;
        } else {
          mutableValue->set_type(AttrType::DATES);
          mutableValue->set_date(date);
        }
      } else if (field_type == AttrType::TEXTS && value_type == AttrType::CHARS) {
        mutableValue->set_text(mutableValue->data());
        if (strlen(mutableValue->get_text()) > 65535) {
          return RC::INVALID_ARGUMENT;
        }
      } else {
        // TODO try to convert the value type to field type
        LOG_WARN("field type mismatch. table=%s, field=%s, field type=%d, value_type=%d",
            table_name, field_meta->name(), field_type, value_type);
        return RC::SCHEMA_FIELD_TYPE_MISMATCH;
      }
    }

    // collect values
    attributes.push_back(update.update_units[i].attribute_name);
    values.push_back(*mutableValue);
  }
  // build filter_stmt
  std::unordered_map<std::string, Table *> table_map;
  table_map.insert(std::pair<std::string, Table *>(std::string(table_name), table));

  FilterStmt *filter_stmt = nullptr;
  RC          rc          = FilterStmt::create(
      db, table, &table_map, update.conditions, static_cast<int>(update.conditions.size()), filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create filter statement. rc=%d:%s", rc, strrc(rc));
    return rc;
  }

  stmt = new UpdateStmt(table, values, update_fields_cnt, filter_stmt, attributes);
  return RC::SUCCESS;
}
