#pragma once

#include "sql/parser/parse_defs.h"
#include "sql/stmt/filter_stmt.h"
#include "sql/stmt/stmt.h"
#include "storage/field/field.h"
#include <vector>

class JoinStmt : public Stmt
{
public:
  JoinStmt() = default;
  explicit JoinStmt(Stmt *left, Stmt *right, FilterStmt *join_condition);
  ~JoinStmt() override;

  StmtType type() const override { return StmtType::JOIN; }

public:
  static RC create(Db *db, std::unordered_map<std::string, Table *> &table_map, std::vector<Field> &all_fields,
      GeneralRelationSqlNode *, Stmt *&stmt);

public:
  Stmt       *left() const { return left_; }
  Stmt       *right() const { return right_; }
  FilterStmt *join_condition() const { return join_condition_; }

private:
  Stmt       *left_           = nullptr;
  Stmt       *right_          = nullptr;
  FilterStmt *join_condition_ = nullptr;
};