//
// Created by hyq on 10/29/23.
//

#include "common/log/log.h"
#include "common/lang/string.h"
#include "sql/stmt/orderby_stmt.h"
#include "sql/stmt/filter_stmt.h"

OrderByStmt::~OrderByStmt() {
  for(OrderByUnit *unit : order_by_units_) {
    delete unit;
  }
  order_by_units_.clear();
}

RC OrderByStmt::create(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables, const std::vector<OrderBy> orderbys, int orderby_num, OrderByStmt *&stmt) {
  RC rc = RC::SUCCESS;
  stmt = nullptr;

  OrderByStmt *tmp_stmt = new OrderByStmt();
  for(int i = 0; i < orderby_num; i++) {
    OrderByUnit *orderby_unit = nullptr;
    rc = create_orderby_unit(db, default_table, tables, orderbys[i], orderby_unit);
    if(rc != RC::SUCCESS) {
      delete tmp_stmt;
      LOG_WARN("failed to create filter unit. condition index=%d", i);
      return rc;
    }
    tmp_stmt->order_by_units_.push_back(orderby_unit);
  }
  stmt = tmp_stmt;
  return rc;
}

// 创建排序单元
RC OrderByStmt::create_orderby_unit(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables, const OrderBy &orderby, OrderByUnit *&orderby_unit) {
  RC rc = RC::SUCCESS;

  bool sort_type = orderby.order;

  Expression *expr = nullptr;
  Table *table = nullptr;
  const FieldMeta *field  = nullptr;
  rc = get_table_and_field(db, default_table, tables, orderby.order_by_attribute, table, field);
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot find attr");
    return rc;
  }

  // 创建字段表达式，通过表名和字段名可以获得该字段的值
  expr = new FieldExpr(table, field);

  // 初始化排序单元
  orderby_unit = new OrderByUnit;
  orderby_unit->set_sort_type(sort_type);
  orderby_unit->set_expr(expr);

  return rc;
}