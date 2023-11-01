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
// Created by WangYunlai on 2022/12/30.
//

#include "sql/operator/join_physical_operator.h"
#include "common/log/log.h"
#include "common/rc.h"
#include "sql/expr/expression.h"
#include "sql/expr/tuple.h"
#include <cstddef>
#include <memory>
#include <vector>

NestedLoopJoinPhysicalOperator::NestedLoopJoinPhysicalOperator(std::unique_ptr<Expression> join_condition)
    : join_condition_(std::move(join_condition))
{
  if (join_condition_ != nullptr) {
    ASSERT(join_condition_->value_type() == BOOLEANS, "join_condition's expression should be BOOLEAN type");
  }
}

RC NestedLoopJoinPhysicalOperator::open(Trx *trx)
{
  if (children_.size() != 2) {
    LOG_WARN("nlj operator should have 2 children");
    return RC::INTERNAL;
  }

  RC rc         = RC::SUCCESS;
  left_         = children_[0].get();
  right_        = children_[1].get();
  right_closed_ = true;
  round_done_   = true;

  rc   = left_->open(trx);
  trx_ = trx;
  return rc;
}

RC NestedLoopJoinPhysicalOperator::next()
{
  // FIXME(CHEN): nlj may have perf issue, maybe replaced with hj or cached tmp result
  RC rc = RC::SUCCESS;
  while ((rc = inner_next()) == RC::SUCCESS) {
    Value value;
    if (join_condition_ == nullptr) {
      return rc;
    }
    rc = join_condition_->get_value(*current_tuple(), value);

    if (rc != RC::SUCCESS) {
      continue;
    }

    if (value.get_boolean()) {
      return rc;
    }
  }

  return rc;
}

RC NestedLoopJoinPhysicalOperator::inner_next()
{
  bool left_need_step = (left_tuple_ == nullptr);
  RC   rc             = RC::SUCCESS;
  if (round_done_) {
    left_need_step = true;
  } else {
    rc = right_next();
    if (rc != RC::SUCCESS) {
      if (rc == RC::RECORD_EOF) {
        left_need_step = true;
      } else {
        return rc;
      }
    } else {
      return rc;  // got one tuple from right
    }
  }

  if (left_need_step) {
    rc = left_next();
    if (rc != RC::SUCCESS) {
      return rc;
    }
  }

  rc = right_next();
  return rc;
}

RC NestedLoopJoinPhysicalOperator::close()
{
  RC rc = left_->close();
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to close left oper. rc=%s", strrc(rc));
  }

  if (!right_closed_) {
    rc = right_->close();
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to close right oper. rc=%s", strrc(rc));
    } else {
      right_closed_ = true;
    }
  }
  return rc;
}

Tuple *NestedLoopJoinPhysicalOperator::current_tuple() { return &joined_tuple_; }

RC NestedLoopJoinPhysicalOperator::left_next()
{
  RC rc = RC::SUCCESS;
  rc    = left_->next();
  if (rc != RC::SUCCESS) {
    return rc;
  }

  left_tuple_ = left_->current_tuple();
  joined_tuple_.set_left(left_tuple_);
  return rc;
}

RC NestedLoopJoinPhysicalOperator::right_next()
{
  RC rc = RC::SUCCESS;
  if (round_done_) {
    if (!right_closed_) {
      rc            = right_->close();
      right_closed_ = true;
      if (rc != RC::SUCCESS) {
        return rc;
      }
    }

    rc = right_->open(trx_);
    if (rc != RC::SUCCESS) {
      return rc;
    }
    right_closed_ = false;

    round_done_ = false;
  }

  rc = right_->next();
  if (rc != RC::SUCCESS) {
    if (rc == RC::RECORD_EOF) {
      round_done_ = true;
    }
    return rc;
  }

  right_tuple_ = right_->current_tuple();
  joined_tuple_.set_right(right_tuple_);
  return rc;
}

StageLoopJoinPhysicalOperator::StageLoopJoinPhysicalOperator(std::unique_ptr<Expression> join_condition)
    : join_condition_(std::move(join_condition))
{
  if (join_condition_ != nullptr) {
    ASSERT(join_condition_->value_type() == BOOLEANS, "join_condition's expression should be BOOLEAN type");
  }
}

RC StageLoopJoinPhysicalOperator::open(Trx *trx)
{
  if (children_.size() != 2) {
    LOG_WARN("nlj operator should have 2 children");
    return RC::INTERNAL;
  }

  RC rc  = RC::SUCCESS;
  left_  = children_[0].get();
  right_ = children_[1].get();

  rc = left_->open(trx);
  if (OB_FAIL(rc)) {
    LOG_WARN("slj fail to open left");
    return rc;
  }
  rc = right_->open(trx);
  if (OB_FAIL(rc)) {
    LOG_WARN("slj fail to open right");
    return rc;
  }
  LOG_INFO("Open JoinOperater SUCCESS.");

  trx_ = trx;
  return rc;
}

RC StageLoopJoinPhysicalOperator::next()
{
  // FIXME(CHEN): nlj may have perf issue, maybe replaced with hj or cached tmp result
  RC rc = RC::SUCCESS;
  while ((rc = inner_next()) == RC::SUCCESS) {
    Value value;
    if (join_condition_ == nullptr) {
      return rc;
    }
    rc = join_condition_->get_value(*current_tuple(), value);

    if (rc != RC::SUCCESS) {
      continue;
    }

    if (value.get_boolean()) {
      return rc;
    }
  }

  return rc;
}

RC StageLoopJoinPhysicalOperator::inner_next()
{
  RC rc = RC::SUCCESS;

  if (is_first_) {
    is_first_ = false;
    rc        = fetch_right_table();
    if (RC::SUCCESS != rc) {
      LOG_DEBUG("Fetch right failed, %s", strrc(rc));
      return rc;
    }
    right_table_iter_ = right_tuple_cache_.end();
  }

  if (right_table_iter_ == right_tuple_cache_.end()) {
    rc = left_->next();
    if (rc == RC::SUCCESS) {
      left_tuple_ = left_->current_tuple();
      joined_tuple_.set_left(left_tuple_);
      right_next();
    } else if (rc == RC::RECORD_EOF) {
      LOG_INFO("left table meet eof");
    } else {
      LOG_ERROR("left table meet err: %s", strrc(rc));
    }
    return rc;
  }

  ++right_table_iter_;
  return rc;
}

RC StageLoopJoinPhysicalOperator::fetch_right_table()
{
  RC     rc         = RC::SUCCESS;
  Tuple *cur_tuple  = nullptr;
  bool   set_schema = false;
  while (RC::SUCCESS == (rc = right_->next())) {
    cur_tuple = right_->current_tuple();
    if (!set_schema) {
      set_schema   = true;
      right_tuple_ = new CacheTuple(cur_tuple->get_row_schema());
    }
    int const          cell_num = cur_tuple->cell_num();
    std::vector<Value> data(cur_tuple->cell_num());
    for (int i = 0; i < cell_num; ++i) {
      cur_tuple->cell_at(i, data[i]);
    }
    right_tuple_cache_.emplace_back(data);
  }

  if (RC::RECORD_EOF == rc) {
    rc = right_->close();
    if (rc != RC::SUCCESS) {
      LOG_WARN("fail to close right, %s", strrc(rc));
      return rc;
    }
    return RC::SUCCESS;
  } else {
    return rc;
  }

  return rc;
}

RC StageLoopJoinPhysicalOperator::close()
{
  RC rc = left_->close();
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to close left oper. rc=%s", strrc(rc));
  }

  return rc;
}

Tuple *StageLoopJoinPhysicalOperator::current_tuple() { return &joined_tuple_; }

RC StageLoopJoinPhysicalOperator::right_next()
{
  if (right_table_iter_ == right_tuple_cache_.end()) {
    right_table_iter_ = right_tuple_cache_.begin();
  } else {
    ++right_table_iter_;
  }

  right_tuple_->set_record(&(*right_table_iter_));
  joined_tuple_.set_right(right_tuple_);

  return RC::SUCCESS;
}
