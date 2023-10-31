#pragma once

#include "sql/stmt/stmt.h"
#include "storage/field/field.h"
#include "storage/table/table.h"
#include <unordered_map>

class SingleTableStmt : public Stmt
{
public:
  SingleTableStmt()  = default;
  ~SingleTableStmt() = default;

  StmtType type() const override { return StmtType::SINGLE_TABLE; }

public:
  static RC create(Db *db, std::vector<Field> &all_fields, GeneralRelationSqlNode *, Stmt *&stmt);

public:
  const std::vector<Field> &query_fields() const { return query_fields_; }
  const std::string         table_name() const { return table_name_; }
  Table                    *table() const { return table_; }

private:
  std::vector<Field> query_fields_;
  std::string        table_name_;
  Table             *table_;
};