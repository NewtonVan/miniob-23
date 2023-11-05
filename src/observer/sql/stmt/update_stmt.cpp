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
#include "common/log/log.h"
#include "common/rc.h"
#include "sql/expr/expression.h"
#include "sql/parser/parse_defs.h"
#include "sql/parser/value.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/db/db.h"
#include "storage/field/field_meta.h"
#include "storage/table/table_meta.h"
#include <string>
#include <unordered_map>
#include <vector>

UpdateStmt::UpdateStmt(Table *table, std::vector<Expression *> &values, int value_amount, FilterStmt *filter_stmt,
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

  const int                                     update_fields_cnt = update.update_units.size();
  std::vector<std::string>                      attributes;
  std::vector<Expression *>                     value_exprs;
  std::unordered_map<std::string, Table *>      table_map;
  std::vector<Table *>                          tables;
  std::unordered_map<std::string, Expression *> expr_mapping;
  for (int i = 0; i < update_fields_cnt; ++i) {
    // check whether field match
    const TableMeta &table_meta = table->table_meta();
    const FieldMeta *field_meta = table_meta.field(update.update_units[i].attribute_name.c_str());
    if (nullptr == field_meta) {
      LOG_WARN("no such field. table_name=%s, field=%s", table_name, update.update_units[i].attribute_name.c_str());
      return RC::SCHEMA_FIELD_NOT_EXIST;
    }

    Expression *src_expr = update.update_units[i].value;
    Expression *dst_expr = nullptr;

    if (src_expr->type() == ExprType::VALUE) {
      ValueExpr *value_ptr = static_cast<ValueExpr *>(src_expr);
      // const AttrType field_type   = field_meta->type();
      // const AttrType value_type   = value_ptr->value_type();
      // Value         *mutableValue = const_cast<Value *>(&value_ptr->get_value());

      // // convert data type if needed
      // RC rc = RC::SUCCESS;
      // rc    = cast(field_meta->nullable(), field_type, value_type, mutableValue);
      // if (rc != RC::SUCCESS) {
      //   if (rc == RC::SCHEMA_FIELD_TYPE_MISMATCH) {
      //     LOG_WARN("field type mismatch. table=%s, field=%s, field type=%d, value_type=%d",
      //       table_name, field_meta->name(), field_type, value_type);
      //   }
      //   return rc;
      // }

      dst_expr = value_ptr;
    } else if (src_expr->type() == ExprType::SUBQUERYTYPE) {
      SubQueryExpression *sub_expr = static_cast<SubQueryExpression *>(src_expr);
      RC                  rc       = sub_expr->create_expression(table_map, tables, expr_mapping, CompOp::EQUAL_TO, db);
      if (rc != RC::SUCCESS) {
        return rc;
      }

      dst_expr = sub_expr;
    } else {
      LOG_ERROR("Unknown expr type: %d", src_expr->type());
    }

    // collect values
    attributes.push_back(update.update_units[i].attribute_name);
    value_exprs.push_back(dst_expr);
  }
  // build filter_stmt
  table_map.insert(std::pair<std::string, Table *>(std::string(table_name), table));

  FilterStmt *filter_stmt = nullptr;
  RC          rc          = FilterStmt::create(
      db, table, &table_map, update.conditions, expr_mapping, static_cast<int>(update.conditions.size()), filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create filter statement. rc=%d:%s", rc, strrc(rc));
    return rc;
  }

  stmt = new UpdateStmt(table, value_exprs, update_fields_cnt, filter_stmt, attributes);
  return RC::SUCCESS;
}

RC UpdateStmt::cast(bool nullable, const AttrType field_type, const AttrType value_type, Value *value)
{
  if (!nullable && value_type == NULLS)
    return RC::INVALID_ARGUMENT_TYPE;
  if (field_type != value_type && !(nullable && value_type == NULLS)) {
    if (field_type == AttrType::DATES && value_type == AttrType::CHARS) {
      int64_t date;
      bool    valid = serialize_date(&date, value->data());
      if (!valid) {
        return RC::INVALID_ARGUMENT_TYPE;
      } else {
        value->set_type(AttrType::DATES);
        value->set_date(date);
      }
    } else if (field_type == AttrType::TEXTS && value_type == AttrType::CHARS) {
      value->set_text(value->data());
      if (strlen(value->get_text()) > 65535) {
        return RC::INVALID_ARGUMENT_TYPE;
      }
    } else if (field_type == AttrType::FLOATS && value_type == AttrType::INTS) {
      value->set_float(value->get_int());
    } else if (field_type == AttrType::INTS && value_type == AttrType::FLOATS) {
      value->set_int(value->get_float());
    } else if (field_type == AttrType::CHARS && value_type == AttrType::INTS) {
      int         i_val = value->get_int();
      std::string s_val = std::to_string(i_val);
      value->set_string(s_val.c_str(), s_val.length());
    } else if (field_type == AttrType::INTS && value_type == AttrType::CHARS) {
      value->set_int(std::stoi(value->get_string()));
    } else if (field_type == AttrType::CHARS && value_type == AttrType::FLOATS) {
      float       f_val = value->get_float();
      std::string s_val = std::to_string(f_val);
      value->set_string(s_val.c_str(), s_val.length());
    } else if (field_type == AttrType::FLOATS && value_type == AttrType::CHARS) {
      value->set_float(std::stod(value->get_string()));
    } else {
      // TODO try to convert the value type to field type
      return RC::SCHEMA_FIELD_TYPE_MISMATCH;
    }
  }

  return RC::SUCCESS;
}