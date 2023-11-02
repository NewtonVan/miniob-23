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

#include "common/log/log.h"
#include "sql/expr/tuple.h"
#include "sql/expr/tuple_cell.h"
#include "sql/operator/physical_operator.h"
#include "sql/parser/parse_defs.h"
#include "sql/parser/value.h"
#include <cstddef>
#include <cstring>
#include <memory>

/**
 * @brief 选择/投影物理算子
 * @ingroup PhysicalOperator
 */
class AggPhysicalOperator : public PhysicalOperator
{
public:
  AggPhysicalOperator(std::vector<AggType>& agg_types, std::vector<TupleCellSpec>& specs, std::vector<TupleCellSpec>& group_by_spec ): sht_(agg_types), agg_types_(agg_types), specs_(specs), group_by_specs_(group_by_spec) {};

  virtual ~AggPhysicalOperator() = default;

  std::string name() const override;
  std::string param() const override;

  PhysicalOperatorType type() const override
  {
    return PhysicalOperatorType::AGG;
  }


  std::vector<std::unique_ptr<Expression>>& expressions() {
    return exprs_;
  }
  

  RC open(Trx *trx) override; // open child 
  RC next() override; // construct a AggregationValue, insert into sht_
  RC close() override;

  Tuple *current_tuple() override;

private:
   /** @return The tuple as an AggregateKey */
  auto MakeAggregateKey(const Tuple *tuple) -> AggregationKey {
    std::vector<Value> vals;
    if(group_by_specs_.empty()) {
      vals.push_back(Value(static_cast<int>(1)));
    } else {
      for(const auto& spec : group_by_specs_) {
        Value val;
        auto rc = tuple->find_cell(spec, val);
        if(rc != RC::SUCCESS) {
          LOG_ERROR("group by cell does not exist");
        }
        vals.push_back(val);
      }
    }
    return {vals};
  }

  /** @return The tuple as an AggregateValue */
  auto MakeAggregateValue(const Tuple *tuple) -> AggregationValue {
    std::vector<Value> vals;
    std::vector<size_t> counts;
    for (const auto& spec : specs_ ) {
      // handle *
      if(strcmp(spec.field_name() , "*") == 0) {
        vals.push_back(Value(1));
        counts.push_back(1);
      } else {
        Value val;
        tuple->find_cell(spec, val);
        vals.push_back(val);
        if(!val.is_null()) {
          counts.push_back(1);
        } else {
          counts.push_back(0);
        }
      }
    }
    return {vals, counts};
  }


  SimpleHashTable sht_;
  std::vector<std::unique_ptr<Expression>> exprs_;
  std::vector<AggType> agg_types_;
  std::vector<TupleCellSpec> specs_;
  std::vector<TupleCellSpec> group_by_specs_;
  std::unique_ptr<SimpleHashTable::Iterator>iter_;
  AggTuple tuple_;

  bool materialized_child_{false};
  bool finish_{false};
};
