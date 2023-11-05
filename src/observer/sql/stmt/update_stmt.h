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

#pragma once

#include "common/rc.h"
#include "sql/expr/expression.h"
#include "sql/parser/value.h"
#include "sql/stmt/filter_stmt.h"
#include "sql/stmt/stmt.h"
#include <string>
#include <vector>

class Table;

/**
 * @brief 更新语句
 * @ingroup Statement
 */
class UpdateStmt : public Stmt
{
public:
  UpdateStmt(Table *table, std::vector<Expression *> &values, int value_amount, FilterStmt *filter_stmt,
      std::vector<std::string> &attribute_name);
  ~UpdateStmt() override;

  StmtType type() const override { return StmtType::UPDATE; }

public:
  static RC create(Db *db, const UpdateSqlNode &update_sql, Stmt *&stmt);
  static RC cast(bool nullable, const AttrType field_type, const AttrType value_type, Value *value);

public:
  Table                          *table() const { return table_; }
  std::vector<Expression *>       values() const { return values_; }
  int                             value_amount() const { return value_amount_; }
  FilterStmt                     *filter_stmt() const { return filter_stmt_; }
  const std::vector<std::string> &attribute_names() const { return attribute_names_; }

private:
  Table                    *table_ = nullptr;
  std::vector<Expression *> values_;
  int                       value_amount_ = 0;
  FilterStmt               *filter_stmt_  = nullptr;
  std::vector<std::string>  attribute_names_;
};
