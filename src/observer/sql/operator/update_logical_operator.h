
#pragma once

#include <string>
#include <vector>

#include "sql/operator/logical_operator.h"
#include "sql/parser/parse_defs.h"
#include "sql/parser/value.h"

/**
 * @brief 插入逻辑算子
 * @ingroup LogicalOperator
 */
class UpdateLogicalOperator : public LogicalOperator
{
public:
  UpdateLogicalOperator(Table *table, std::vector<Expression *> values, std::vector<std::string> field_names);
  virtual ~UpdateLogicalOperator() = default;

  LogicalOperatorType type() const override { return LogicalOperatorType::UPDATE; }

  Table                     *table() const { return table_; }
  std::vector<Expression *> &values() { return values_; }
  std::vector<std::string>  &field_names() { return field_names_; }

private:
  Table                    *table_ = nullptr;
  std::vector<Expression *> values_;
  std::vector<std::string>  field_names_;
};