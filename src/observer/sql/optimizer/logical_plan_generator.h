/* Copyright (c) 2023 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2023/08/16.
//

#pragma once

#include <memory>

#include "common/rc.h"
#include "sql/stmt/join_stmt.h"
#include "sql/stmt/update_stmt.h"

class Stmt;
class CalcStmt;
class SelectStmt;
class FilterStmt;
class OrderByStmt;
class InsertStmt;
class UpdateStmt;
class DeleteStmt;
class ExplainStmt;
class LogicalOperator;

class LogicalPlanGenerator
{
public:
  LogicalPlanGenerator()          = default;
  virtual ~LogicalPlanGenerator() = default;

  RC create(Stmt *stmt, std::unique_ptr<LogicalOperator> &logical_operator);

private:
  RC create_plan(CalcStmt *calc_stmt, std::unique_ptr<LogicalOperator> &logical_operator);
  RC create_plan(JoinStmt *join_stmt, std::unique_ptr<LogicalOperator> &logical_operator);
  RC create_plan(SelectStmt *select_stmt, std::unique_ptr<LogicalOperator> &logical_operator);
  RC create_plan(FilterStmt *filter_stmt, std::unique_ptr<LogicalOperator> &logical_operator);
  RC create_plan(InsertStmt *insert_stmt, std::unique_ptr<LogicalOperator> &logical_operator);
  RC create_plan(UpdateStmt *update_stmt, std::unique_ptr<LogicalOperator> &logical_operator);
  RC create_plan(DeleteStmt *delete_stmt, std::unique_ptr<LogicalOperator> &logical_operator);
  RC create_plan(ExplainStmt *explain_stmt, std::unique_ptr<LogicalOperator> &logical_operator);
  RC create_plan_for_subquery(const FilterUnit *filter, std::unique_ptr<LogicalOperator> &logical_operator);
  RC generate_conjunction_expression(const std::vector<FilterUnit *>& filter_units, std::unique_ptr<Expression>& expression);
  RC generate_conjunction_or_comparison_expression(const FilterUnit* filter_unit, std::unique_ptr<Expression>& expressions);
};