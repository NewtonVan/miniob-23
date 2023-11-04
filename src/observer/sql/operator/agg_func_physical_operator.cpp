//
// Created by liuyongqiang.10086 on 10/27/23.
//

#include <cmath>
#include <cstddef>
#include <cstring>
#include "common/defs.h"
#include "common/log/log.h"
#include "sql/expr/tuple.h"
#include "sql/expr/tuple_cell.h"
#include "sql/operator/physical_operator.h"
#include "sql/operator/agg_func_physical_operator.h"
#include "sql/parser/parse_defs.h"
#include "sql/parser/value.h"

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
    empty_table_ = true;
    ASSERT(children_.size() == 1, "agg should have just one child");
    children_[0]->open(trx);
    return RC::SUCCESS;
}

RC AggPhysicalOperator::next() {
  if (finish_) {
    return RC::RECORD_EOF;
  }

  if (!materialized_child_) {
    while (children_[0]->next() == RC::SUCCESS) {
      empty_table_ = false;
      Tuple* tmp_tuple = children_[0]->current_tuple();
      // construct AggregateKey AggregateValue
      auto agg_key = MakeAggregateKey(tmp_tuple);
      auto agg_val = MakeAggregateValue(tmp_tuple);
    
      sht_.InsertCombine(agg_key, agg_val);
    }

    // todo(lyq) (handle empty table)
    if(empty_table_) {
      // construct a result and  return RC::RECORD_EOF on next call on next_tuple
      std::vector<Value> values;
      // default agg value
      for (int i = 0; i < agg_types_.size(); i++) {
        switch (agg_types_[i]) {
        case COUNT_STAR:
          values.push_back(Value::get_null(AttrType::INTS));
          break;
        case COUNT_AGG:
          values.push_back(Value::get_null(AttrType::INTS));
          break;
        case SUM_AGG:
        case MIN_AGG:
        case MAX_AGG:
        case AVG_AGG:
        // deal with float conversion in CombineAggregateValues
          Value val;
          val.set_type(AttrType::NULLS);
          values.push_back(val);
          break;
        }
      }

      // default group by field todo(lyq)
      for(int i =0; i < group_by_specs_.size(); i++) {
        Value val;
        val.set_type(AttrType::NULLS);
        values.push_back(val);
      }
      
      materialized_child_ = true;
      tuple_.set_tuple(values , agg_specs_, group_by_specs_);
      return RC::SUCCESS; 
    }

    iter_ = std::make_unique<SimpleHashTable::Iterator>(sht_.Begin());

    // handle avg in sht_;
    for(size_t i = 0; i < agg_types_.size(); i++) {
      // fix avg on null field
        if(agg_types_[i] == AggType::AVG_AGG) {
            for(auto iter = sht_.Begin(); iter.operator!=(sht_.End()); ++iter) {
                Value& val = iter.Val().aggregates[i];
                if(val.is_null()) {
                  continue;
                }

                size_t count = iter.Val().not_null_count_[i];
                switch (val.attr_type()) {
                case INTS:
                    if(count != 0) {
                      val.set_float(static_cast<float>(val.get_int())/count);
                    }else{
                      // set null
                      val.set_type(AttrType::NULLS);
                    }
                break;
                case FLOATS:
                  if(count != 0) {
                      val.set_float(val.get_float()/ count);
                    }else{
                      // set null 
                      val.set_type(AttrType::NULLS);
                    }
                break;
                default:
                    LOG_ERROR("INVALID AVG on type%d", val.attr_type());
                    return RC::BAD_AGG; // todo(lyq) check type in generate physical paln 
                }
            }
        }
    }
    materialized_child_ = true;
  }

  if (empty_table_ || iter_->operator==(sht_.End())) {
    finish_ = true;
    return RC::RECORD_EOF;
  }

  std::vector<Value> values;

  // make output schema values
  for (auto &val : iter_->Val().aggregates) {
    values.push_back(val);
  }

  // close group by for now
  if(!group_by_specs_.empty()) {
    for (auto &val : iter_->Key().group_bys_) {
      values.push_back(val);
    }
  }

  tuple_.set_tuple(values , agg_specs_, group_by_specs_);
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



