//
// Created by hyq on 10/29/23.
//

#ifndef MINIDB_ORDERBY_STMT_H
#define MINIDB_ORDERBY_STMT_H

#include "sql/expr/expression.h"

class Db;
class Table;
class FieldMeta;

class OrderByUnit {
public:
  OrderByUnit() = default;
  ~OrderByUnit() {
    if(expr_) {
      delete expr_;
      expr_ = nullptr;
    }
  }

  void set_sort_type(bool sort_type) {
    is_asc_ = sort_type;
  }

  bool sort_type() const {
    return is_asc_;
  }

  void set_expr(Expression *expr) {
    expr_ = expr;
  }

  Expression *expr() const {
    return expr_;
  }

private:
  bool is_asc_ = true;
  Expression *expr_ = nullptr;
};


class OrderByStmt {
public:
  OrderByStmt() = default;
  virtual ~OrderByStmt();

  const std::vector<OrderByUnit *> &orderby_units() const {
    return order_by_units_;
  }

  static RC create(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
      const std::vector<OrderBy> orderbys, int orderby_num, OrderByStmt *&stmt);

  static RC create_orderby_unit(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
      const OrderBy &orderby, OrderByUnit *&orderby_unit);

private:
  std::vector<OrderByUnit *> order_by_units_;
};





#endif  // MINIDB_ORDERBY_STMT_H
