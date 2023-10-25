#pragma once

#include <vector>
#include "sql/operator/physical_operator.h"
#include "sql/parser/parse.h"

class InsertStmt;

/**
 * @brief 修改物理算子
 * @ingroup PhysicalOperator
 */
class UpdatePhysicalOperator : public PhysicalOperator
{
public:
  UpdatePhysicalOperator(Table *table, Value &value, const std::string field_name);

  virtual ~UpdatePhysicalOperator() = default;

  PhysicalOperatorType type() const override { return PhysicalOperatorType::UPDATE; }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;

  Tuple *current_tuple() override { return nullptr; }

private:
  Table      *table_ = nullptr;
  Value       value_;
  std::string field_name_;
  Trx        *trx_ = nullptr;
};
