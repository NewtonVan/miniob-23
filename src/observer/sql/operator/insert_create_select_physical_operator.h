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
      std::string table_name,
      std::vector<AttrInfoSqlNode>&& attr_infos) : db_(db), fields_(fields), table_name_(table_name), table_select_attr_infos_(std::move(attr_infos)) {}

  virtual ~InsertCreateSelectPhysicalOperator() = default;

  PhysicalOperatorType type() const override
  {
    return PhysicalOperatorType::INSERT;
  }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;

  Tuple *current_tuple() override { return nullptr; }

  RC insert_record(std::vector<Value>&& values);

  void create_table_for_exprs(int& left_not_in_right_count);
  void create_table_for_fields(int& left_not_in_right_count);

private:
  Db* db_;
  const std::vector<Field> fields_;
  string table_name_;
  std::vector<AttrInfoSqlNode>  table_select_attr_infos_;

  Trx *trx_;
  bool is_first_ = true;
  Table* table_ = nullptr;
};

#endif  // MINIDB_INSERT_CREATE_SELECT_PHYSICAL_OPERATOR_H
