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

#include "sql/expr/tuple.h"
#include "sql/operator/physical_operator.h"
#include "sql/parser/parse_defs.h"

/**
 * @brief 选择/投影物理算子
 * @ingroup PhysicalOperator
 */
class AggPhysicalOperator : public PhysicalOperator
{
public:
  AggPhysicalOperator(std::vector<AggType>& agg_types):sht_(agg_types) {};

  virtual ~AggPhysicalOperator() = default;

  void add_expressions(std::vector<std::unique_ptr<Expression>> &&expressions)
  {
    
  }

  PhysicalOperatorType type() const override
  {
    return PhysicalOperatorType::AGG;
  }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;

  int cell_num() const
  {
  }


  Tuple *current_tuple() override;

private:
  SimpleHashTable sht_;
};