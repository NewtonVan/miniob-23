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
// Created by Wangyunlai on 2022/12/15
//

#include "sql/operator/project_logical_operator.h"
#include "sql/expr/expression.h"
#include <memory>
#include <vector>

ProjectLogicalOperator::ProjectLogicalOperator(const std::vector<Field> &fields) : fields_(fields) {}

ProjectLogicalOperator::ProjectLogicalOperator(
    const std::vector<Field> &fields, std::vector<std::unique_ptr<Expression>> &&expressions)
    : fields_(fields)
{
  expressions_.swap(expressions);
  use_project_exprs_ = true;
}