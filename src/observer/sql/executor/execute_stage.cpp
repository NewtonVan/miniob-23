/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Longda on 2021/4/13.
//

#include <memory>
#include <string>
#include <sstream>

#include "sql/executor/execute_stage.h"

#include "common/log/log.h"
#include "session/session.h"
#include "event/storage_event.h"
#include "event/sql_event.h"
#include "event/session_event.h"
#include "sql/expr/expression.h"
#include "sql/operator/project_physical_operator.h"
#include "sql/parser/parse_defs.h"
#include "sql/stmt/stmt.h"
#include "sql/stmt/select_stmt.h"
#include "storage/default/default_handler.h"
#include "sql/executor/command_executor.h"
#include "sql/operator/calc_physical_operator.h"

using namespace std;
using namespace common;

RC ExecuteStage::handle_request(SQLStageEvent *sql_event)
{
  RC                                  rc                = RC::SUCCESS;
  const unique_ptr<PhysicalOperator> &physical_operator = sql_event->physical_operator();
  if (physical_operator != nullptr) {
    return handle_request_with_physical_operator(sql_event);
  }

  SessionEvent *session_event = sql_event->session_event();

  Stmt *stmt = sql_event->stmt();
  if (stmt != nullptr) {
    CommandExecutor command_executor;
    rc = command_executor.execute(sql_event);
    session_event->sql_result()->set_return_code(rc);
  } else {
    return RC::INTERNAL;
  }
  return rc;
}

RC ExecuteStage::handle_request_with_physical_operator(SQLStageEvent *sql_event)
{
  RC rc = RC::SUCCESS;

  Stmt *stmt = sql_event->stmt();
  ASSERT(stmt != nullptr, "SQL Statement shouldn't be empty!");

  unique_ptr<PhysicalOperator> &physical_operator = sql_event->physical_operator();
  ASSERT(physical_operator != nullptr, "physical operator should not be null");

  // TODO 这里也可以优化一下，是否可以让physical operator自己设置tuple schema
  TupleSchema schema;
  switch (stmt->type()) {
    case StmtType::SELECT: {
      SelectStmt *select_stmt     = static_cast<SelectStmt *>(stmt);
      bool        with_table_name = select_stmt->tables().size() > 1;

      //WIP(lyq) construct agg schema
      if(select_stmt->is_agg()) {
        // use alias
        for(const auto& agg_field : select_stmt->all_agg_fields()) {
          string alias;
          alias += SelectStmt::agg_field::name(agg_field.func_);
          alias += "(";
          if(agg_field.field_is_star) {
            alias += "*";
          } else {
            alias += agg_field.field_.field_name();
          }
          alias += ")";
          std::transform(alias.begin(), alias.end(), alias.begin(), ::toupper);
          schema.append_cell(alias.c_str());
        }
      } else if (select_stmt->use_project_exprs()) {
        ProjectPhysicalOperator *proj_oper = static_cast<ProjectPhysicalOperator *>(physical_operator.get());
        for (const std::unique_ptr<Expression> &expr : proj_oper->expressions()) {
          if (expr->type() == ExprType::FIELD) {
            FieldExpr *attr = static_cast<FieldExpr *>(expr.get());
            if (strlen(attr->field_alias()) > 0) {
              schema.append_cell(attr->field_alias());
            }
            if (with_table_name) {
              schema.append_cell(attr->table_name(), attr->field_name());
            } else {
              schema.append_cell(attr->field_name());
            }
          } else {
            schema.append_cell(expr->name().c_str());
          }
        }
      } else {
        for (const Field &field : select_stmt->query_fields()) {
          if (with_table_name) {
            schema.append_cell(field.table_name(), field.field_name());
          } else {
            schema.append_cell(field.field_name());
          }
        }
      }
    } break;

    case StmtType::CALC: {
      CalcPhysicalOperator *calc_operator = static_cast<CalcPhysicalOperator *>(physical_operator.get());
      for (const unique_ptr<Expression> &expr : calc_operator->expressions()) {
        schema.append_cell(expr->name().c_str());
      }
    } break;

    case StmtType::EXPLAIN: {
      schema.append_cell("Query Plan");
    } break;
    default: {
      // 只有select返回结果
    } break;
  }

  SqlResult *sql_result = sql_event->session_event()->sql_result();
  sql_result->set_tuple_schema(schema);
  sql_result->set_operator(std::move(physical_operator));
  return rc;
}
