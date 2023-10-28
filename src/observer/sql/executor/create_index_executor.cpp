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
// Created by Wangyunlai on 2023/4/25.
//

#include "sql/executor/create_index_executor.h"
#include "sql/stmt/create_index_stmt.h"
#include "event/sql_event.h"
#include "event/session_event.h"
#include "session/session.h"
#include "common/log/log.h"
#include "storage/table/table.h"

RC CreateIndexExecutor::execute(SQLStageEvent *sql_event)
{
  Stmt *stmt = sql_event->stmt();
  Session *session = sql_event->session_event()->session();
  ASSERT(stmt->type() == StmtType::CREATE_INDEX, 
         "create index executor can not run this command: %d", static_cast<int>(stmt->type()));

  CreateIndexStmt *create_index_stmt = static_cast<CreateIndexStmt *>(stmt);
  
  Trx *trx = session->current_trx();
  Table *table = create_index_stmt->table();
  auto rc = RC::SUCCESS;
  int mutil = create_index_stmt->field_metas().size();
  std::vector<FieldMeta> filed_metas;
  for(int i = 0; i < create_index_stmt->field_metas().size(); i++) {
    auto tmp = create_index_stmt->field_metas()[i];
    FieldMeta file_meta(tmp->name(), tmp->type(), tmp->offset(), tmp->len(), tmp->visible(), tmp->nullable());
    filed_metas.emplace_back(file_meta);
  }
  for(int i = 0; i < filed_metas.size(); i++) {
    const auto file_meta = filed_metas[i];
    const auto index_name = create_index_stmt->index_name() + "_" + file_meta.name();
    rc = table->create_index(trx, &file_meta, index_name.c_str(), create_index_stmt->unique(), mutil);
    if(rc != RC::SUCCESS) {
      return rc;
    }
  }
  return rc;
}