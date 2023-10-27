
#include "sql/operator/join_logical_operator.h"
#include "sql/expr/expression.h"
#include <memory>
#include <utility>
JoinLogicalOperator::JoinLogicalOperator(std::unique_ptr<Expression> expression)
{
  expressions_.emplace_back(std::move(expression));
}