//
// Created by liuyongqiang.10086 on 10/27/23.
//

#include "sql/expr/tuple.h"
#include "sql/operator/physical_operator.h"
#include "sql/operator/agg_func_physical_operator.h"
#include <cmath>




std::string AggPhysicalOperator::name() const  {
    return std::string("AGG");
}

std::string AggPhysicalOperator::param() const  {
    //todo(lyq)
    return std::string("");
}

RC AggPhysicalOperator::open(Trx *trx) {
    materialized_child_ = false;
    finish_ = false;
    ASSERT(children_.size() == 1, "agg should have just one child");
    children_[0]->open(trx);
    return RC::SUCCESS;
}

RC AggPhysicalOperator::next() {
  if (finish_) {
    // todo(recheck)
    return RC::EMPTY;
  }
  std::vector<Value> values;
  if (!materialized_child_) {
    while (children_[0]->next() == RC::SUCCESS) {
      Tuple* tmp_tuple = children_[0]->current_tuple();
      // construct AggregateKey AggregateValue
      auto agg_key = MakeAggregateKey(tmp_tuple);
      auto agg_val = MakeAggregateValue(tmp_tuple);
      sht_.InsertCombine(agg_key, agg_val);
    }
    iter_ = std::make_unique<SimpleHashTable::Iterator>(sht_.Begin());
    materialized_child_ = true;
  }

  if (iter_->operator==(sht_.End())) {
    finish_ = true;
    return RC::EMPTY;
  }

    // todo(lyq) no group by
  // make output schema values
//   for (auto &val : iter_->Key().group_bys_) {
//     values.push_back(val);
//   }
  for (auto &val : iter_->Val().aggregates) {
    values.push_back(val);
  }

  tuple_.set_tuple(iter_->Val() , specs_);
  iter_->operator++();

  return RC::SUCCESS;
}

RC AggPhysicalOperator::close() {
  if (!children_.empty()) {
    children_[0]->close();
  }
  return RC::SUCCESS;
}

Tuple * AggPhysicalOperator::current_tuple() {
    // use iterator to tranverse sht_
    return  &tuple_;
}



