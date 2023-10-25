
#pragma once

#include <string>
#include <vector>

#include "sql/operator/logical_operator.h"
#include "sql/parser/parse_defs.h"

/**
 * @brief 插入逻辑算子
 * @ingroup LogicalOperator
 */
class UpdateLogicalOperator : public LogicalOperator
{
public:
  UpdateLogicalOperator(Table *table, Value value, std::string field_name);
  virtual ~UpdateLogicalOperator() = default;

  LogicalOperatorType type() const override { return LogicalOperatorType::UPDATE; }

  Table             *table() const { return table_; }
  Value             &value() { return value_; }
  const std::string &field_name() const { return field_name_; }

private:
  Table      *table_ = nullptr;
  Value       value_;
  std::string field_name_ = nullptr;
};