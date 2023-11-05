//
// Created by hyq on 11/5/23.
//

#ifndef MINIDB_INSERT_CREATE_SELECT_LOGICAL_OPERATOR_H
#define MINIDB_INSERT_CREATE_SELECT_LOGICAL_OPERATOR_H

#include "sql/operator/logical_operator.h"
#include "sql/parser/parse_defs.h"

class InsertCreateSelectLogicalOperator : public LogicalOperator
{
public:
  InsertCreateSelectLogicalOperator(Db * db,
      const std::vector<Field> &fields,
      std::string table_name,
      std::vector<AttrInfoSqlNode>&& attr_infos) : db_(db), fields_(fields), table_name_(table_name), table_select_attr_infos_(std::move(attr_infos)) {}

  virtual ~InsertCreateSelectLogicalOperator() = default;

  LogicalOperatorType type() const override
  {
    return LogicalOperatorType::INSERT_CREATE_SELECT;
  }

  const std::vector<Field>                       &fields() { return fields_; }
  Db*                                             DB() { return db_; }
  std::string                                     table_name() { return table_name_; }
  std::vector<AttrInfoSqlNode>&                   table_select_attr_infos() { return table_select_attr_infos_; }

private:
  Db* db_;
  const std::vector<Field> fields_;
  std::string table_name_;
  std::vector<AttrInfoSqlNode>        table_select_attr_infos_;
};

#endif  // MINIDB_INSERT_CREATE_SELECT_LOGICAL_OPERATOR_H
