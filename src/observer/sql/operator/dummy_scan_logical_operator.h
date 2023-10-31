#pragma once

#include "sql/operator/logical_operator.h"
class DummyScanLogicalOperator : public LogicalOperator
{
public:
  DummyScanLogicalOperator()          = default;
  virtual ~DummyScanLogicalOperator() = default;
  LogicalOperatorType type() const override { return LogicalOperatorType::DUMMY; }
};