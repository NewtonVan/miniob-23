#pragma once

#include "common/rc.h"
#include "sql/stmt/filter_stmt.h"
#include "sql/stmt/stmt.h"

class Table;

/**
* @brief 更新语句
* @ingroup Statement
*/
class AggregationStmt : public Stmt
{
public:
   AggregationStmt(Table *table, const std::vector<AggregationFuncSqlNode>& agg_funcs):table_(table), agg_funcs_(agg_funcs) {};
   ~AggregationStmt() override;

   StmtType type() const override { return StmtType::AGG; }

   static RC create(Db *db, const SelectSqlNode &select_sql, Stmt *&stmt);

private:
   Table* table_;
   Stmt* child_; // filter or table scan (only one child)
   std::vector<AggregationFuncSqlNode> agg_funcs_;
};





