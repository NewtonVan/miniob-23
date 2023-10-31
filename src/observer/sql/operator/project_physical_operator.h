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
// Created by WangYunlai on 2022/07/01.
//

#pragma once

#include "sql/expr/expression.h"
#include "sql/expr/tuple.h"
#include "sql/operator/physical_operator.h"
#include <cstddef>
#include <memory>
#include <utility>
#include <vector>

/**
 * @brief 选择/投影物理算子
 * @ingroup PhysicalOperator
 */
class ProjectPhysicalOperator : public PhysicalOperator
{
public:
  ProjectPhysicalOperator(std::vector<std::unique_ptr<Expression>> &expressions) : expressions_(std::move(expressions))
  {}

  virtual ~ProjectPhysicalOperator() = default;

  void                                      add_expressions(std::vector<std::unique_ptr<Expression>> &&expressions) {}
  void                                      add_projection(const Table *table, const FieldMeta *field);
  void                                      init_specs();
  std::vector<std::unique_ptr<Expression>> &expressions() { return expressions_; }

  PhysicalOperatorType type() const override { return PhysicalOperatorType::PROJECT; }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;

  int cell_num() const { return tuple_.cell_num(); }

  Tuple *current_tuple() override;

  void toggle_use_project_exprs()
  {
    use_project_exprs_ = true;
    expression_tuple_  = new ExpressionTuple(expressions_);
    tuple_.set_tuple(expression_tuple_);
  }
  bool use_project_exprs() const { return use_project_exprs_; }

private:
  ProjectTuple                             tuple_;
  std::vector<std::unique_ptr<Expression>> expressions_;
  bool                                     use_project_exprs_ = false;
  ExpressionTuple                         *expression_tuple_  = nullptr;
};
