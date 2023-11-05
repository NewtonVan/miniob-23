//
// Created by hyq on 11/5/23.
//

#ifndef MINIDB_INSERT_CREATE_SELECT_PHYSICAL_OPERATOR_H
#define MINIDB_INSERT_CREATE_SELECT_PHYSICAL_OPERATOR_H

#include "sql/operator/physical_operator.h"
#include "sql/parser/parse.h"

class InsertCreateSelectPhysicalOperator : public PhysicalOperator
{
public:
  InsertCreateSelectPhysicalOperator(Db * db,
      const std::vector<Field> &fields,
      std::string table_name) : db_(db), fields_(fields), table_name_(table_name){}

  virtual ~InsertCreateSelectPhysicalOperator() = default;

  PhysicalOperatorType type() const override
  {
    return PhysicalOperatorType::INSERT;
  }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;

  Tuple *current_tuple() override { return nullptr; }

  RC make_record(std::vector<Value>& values);

private:
  Db* db_;
  const std::vector<Field> fields_;

  bool is_first_ = true;
  Table* table_ = nullptr;
  string table_name_;
  Trx *trx_;
};

#endif  // MINIDB_INSERT_CREATE_SELECT_PHYSICAL_OPERATOR_H
