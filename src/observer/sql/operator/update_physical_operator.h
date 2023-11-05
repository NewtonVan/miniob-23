#pragma once

#include <string>
#include <vector>
#include "sql/operator/physical_operator.h"
#include "sql/parser/parse.h"
#include "sql/parser/value.h"
#include "storage/field/field_meta.h"

class InsertStmt;

/**
 * @brief 修改物理算子
 * @ingroup PhysicalOperator
 */
class UpdatePhysicalOperator : public PhysicalOperator
{
public:
  UpdatePhysicalOperator(Table *table, std::vector<Expression *> &values, std::vector<std::string> &field_names);

  virtual ~UpdatePhysicalOperator() = default;

  PhysicalOperatorType type() const override { return PhysicalOperatorType::UPDATE; }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;

  Tuple *current_tuple() override { return nullptr; }

  RC gen_values();

private:
  Table                         *table_ = nullptr;
  std::vector<Expression *>      value_exprs_;
  std::vector<Value>             values_;
  std::vector<std::string>       field_names_;
  std::vector<const FieldMeta *> field_metas_;
  Trx                           *trx_ = nullptr;
};
