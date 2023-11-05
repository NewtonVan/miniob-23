
#include "sql/stmt/join_stmt.h"
#include "common/rc.h"
#include "sql/parser/parse_defs.h"
#include "sql/stmt/filter_stmt.h"
#include "sql/stmt/single_table_stmt.h"
#include "sql/stmt/stmt.h"
#include "storage/field/field.h"
#include <string>
#include <unordered_map>
#include <vector>

JoinStmt::JoinStmt(Stmt *left, Stmt *right, FilterStmt *join_condition)
    : left_(left), right_(right), join_condition_(join_condition)
{}

JoinStmt::~JoinStmt()
{
  if (left_ != nullptr) {
    delete left_;
    left_ = nullptr;
  }
  if (right_ != nullptr) {
    delete right_;
    right_ = nullptr;
  }
  if (join_condition_ != nullptr) {
    delete join_condition_;
    join_condition_ = nullptr;
  }
}

RC JoinStmt::create(Db *db, std::unordered_map<std::string, Table *> &table_map, std::vector<Field> &all_fields,
    GeneralRelationSqlNode *rel, Stmt *&stmt)
{
  JoinSqlNode *join = std::get<JoinSqlNode *>(rel->relation);

  RC    rc   = RC::SUCCESS;
  Stmt *left = nullptr;
  if (join->left->type == REL_TABLE) {
    rc = SingleTableStmt::create(db, all_fields, join->left, left);
    if (rc != RC::SUCCESS) {
      LOG_WARN("cannot construct left table stmt, %s", std::get<std::string>(join->left->relation).c_str());
      return rc;
    }
  } else {
    rc = create(db, table_map, all_fields, join->left, left);
    if (rc != RC::SUCCESS) {
      return rc;
    }
  }

  Stmt *right = nullptr;
  if (join->right->type == REL_TABLE) {
    rc = SingleTableStmt::create(db, all_fields, join->right, right);
    if (rc != RC::SUCCESS) {
      LOG_WARN("cannot construct right table stmt, %s", std::get<std::string>(join->left->relation).c_str());
      return rc;
    }
  } else {
    rc = create(db, table_map, all_fields, join->right, right);
    if (rc != RC::SUCCESS) {
      return rc;
    }
  }

  FilterStmt                                   *join_condition = nullptr;
  std::unordered_map<std::string, Expression *> expr_mapping;
  rc = FilterStmt::create(
      db, nullptr, &table_map, join->conditions, expr_mapping, join->conditions.size(), join_condition);
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot construct filter stmt");
    return rc;
  }

  stmt = new JoinStmt(left, right, join_condition);

  return RC::SUCCESS;
}