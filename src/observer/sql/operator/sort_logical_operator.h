//
// Created by hyq on 10/29/23.
//

#ifndef MINIDB_SORT_LOGICAL_OPERATOR_H
#define MINIDB_SORT_LOGICAL_OPERATOR_H

#include "sql/operator/logical_operator.h"

class OrderByStmt;

class SortLogicalOperator : public LogicalOperator {
public:
  SortLogicalOperator(const std::vector<Field>& all_fields, OrderByStmt *order_stmt) : all_fields_(all_fields),  orderby_stmt_(order_stmt) {}

  virtual ~SortLogicalOperator() = default;

  LogicalOperatorType type() const override
  {
    return LogicalOperatorType::SORT;
  }

  OrderByStmt* orderby_stmt() { return orderby_stmt_; }

  std::vector<Field> all_fields() { return all_fields_; }

private:
      OrderByStmt *orderby_stmt_ = nullptr;
      std::vector<Field> all_fields_;
};



#endif  // MINIDB_SORT_LOGICAL_OPERATOR_H
