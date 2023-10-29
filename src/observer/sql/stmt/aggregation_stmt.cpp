//
// Created by liuyongqiang.10086 on 10/27/23.
//

#include "aggregation_stmt.h"
#include "sql/stmt/select_stmt.h"

RC AggregationStmt::create(Db *db, const SelectSqlNode &select_sql, Stmt *&stmt) {
    // db is default database 
    // resolved as relation_name field of RelAttrSqlNode which relation_name is empty
    SelectStmt::create(db, select_sql, stmt);
    
}