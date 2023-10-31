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
// Created by Wangyunlai on 2022/6/5.
//

#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <memory>

#include "common/rc.h"
#include "sql/expr/expression.h"
#include "sql/parser/parse_defs.h"
#include "sql/stmt/join_stmt.h"
#include "sql/stmt/stmt.h"
#include "storage/field/field.h"

class FieldMeta;
class FilterStmt;
class OrderByStmt;
class Db;
class Table;

/**
 * @brief 表示select语句
 * @ingroup Statement
 */
class SelectStmt : public Stmt
{
public:
  SelectStmt() = default;
  ~SelectStmt() override;

  StmtType type() const override { return StmtType::SELECT; }

public:
  static RC create(Db *db, const SelectSqlNode &select_sql, Stmt *&stmt);
  // TODO(chen): handle alias issue
  static RC collectJoinTables(Db *db, GeneralRelationSqlNode *rel, std::vector<Table *> &tables,
      std::unordered_map<std::string, Table *> &table_map, std::unordered_map<std::string, std::string> &alias_map);
  static RC collectQueryFields(
      const std::vector<Expression *> &select_expressions, std::vector<RelAttrSqlNode> &query_attr, bool &field_only);
  static RC collectQueryFieldsInExpression(
      Expression *select_expr, std::vector<RelAttrSqlNode> &query_attr, bool &field_only);
  static RC rewrite_attr_expr_to_field_expr(Db *db, Table *default_table,
      std::unordered_map<std::string, Table *> *tables, Expression *old_expr, std::unique_ptr<Expression> &ret_expr);
  static RC get_table_and_field(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
      const RelAttrSqlNode &attr, Table *&table, const FieldMeta *&field);

public:
  const std::vector<Table *>               &tables() const { return tables_; }
  const std::vector<Field>                 &query_fields() const { return query_fields_; }
  FilterStmt                               *filter_stmt() const { return filter_stmt_; }
  JoinStmt                                 *join_stmt() const { return join_stmt_; }
  OrderByStmt                              *orderby_stmt() const { return orderby_stmt_; }
  std::vector<std::unique_ptr<Expression>> &project_exprs() { return project_exprs_; }
  bool                                      use_project_exprs() const { return use_project_exprs_; }

private:
  std::vector<Field>                       query_fields_;
  std::vector<Table *>                     tables_;
  std::vector<std::unique_ptr<Expression>> project_exprs_;
  FilterStmt                              *filter_stmt_       = nullptr;
  JoinStmt                                *join_stmt_         = nullptr;
  OrderByStmt                             *orderby_stmt_      = nullptr;
  bool                                     use_project_exprs_ = false;
};
