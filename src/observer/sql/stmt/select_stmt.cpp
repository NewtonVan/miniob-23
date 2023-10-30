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
// Created by Wangyunlai on 2022/6/6.
//

#include "sql/stmt/select_stmt.h"
#include "sql/parser/parse_defs.h"
#include "sql/parser/value.h"
#include "sql/stmt/filter_stmt.h"
#include "common/log/log.h"
#include "common/lang/string.h"
#include "storage/db/db.h"
#include "storage/field/field.h"
#include "storage/field/field_meta.h"
#include "storage/table/table.h"
#include <cstring>
#include <sys/socket.h>

SelectStmt::~SelectStmt()
{
  if (nullptr != filter_stmt_) {
    delete filter_stmt_;
    filter_stmt_ = nullptr;
  }
}

static void wildcard_fields(Table *table, std::vector<Field> &field_metas)
{
  const TableMeta &table_meta = table->table_meta();
  const int field_num = table_meta.field_num();
  for (int i = table_meta.sys_field_num(); i < field_num; i++) {
    field_metas.push_back(Field(table, table_meta.field(i)));
  }
}

// static void wildcard_agg_fields(Table *table, AggFuncType func, std::vector<SelectStmt::agg_field>& fields) {
//   const TableMeta &table_meta = table->table_meta();
//   const int field_num = table_meta.field_num();
//   for (int i = table_meta.sys_field_num(); i < field_num; i++) {
//     fields.push_back(SelectStmt::agg_field(func, Field(table,table_meta.field(i))));
//   }
// }


RC SelectStmt::create(Db *db, const SelectSqlNode &select_sql, Stmt *&stmt)
{
  if (nullptr == db) {
    LOG_WARN("invalid argument. db is null");
    return RC::INVALID_ARGUMENT;
  }

  // collect tables in `from` statement
  std::vector<Table *> tables;
  std::unordered_map<std::string, Table *> table_map;
  for (size_t i = 0; i < select_sql.relations.size(); i++) {
    const char *table_name = select_sql.relations[i].c_str();
    if (nullptr == table_name) {
      LOG_WARN("invalid argument. relation name is null. index=%d", i);
      return RC::INVALID_ARGUMENT;
    }
    // select_sql.conditions.data()->right_value.data()
    Table *table = db->find_table(table_name);
    if (nullptr == table) {
      LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }

    tables.push_back(table);
    table_map.insert(std::pair<std::string, Table *>(table_name, table));
  }


  Table *default_table = nullptr;
  if (tables.size() == 1) {
    default_table = tables[0];
  }

  bool is_agg = !select_sql.agg_funcs.empty();
  if(is_agg && !select_sql.attributes.empty()) {
    return RC::BAD_AGG;
  }


  std::vector<agg_field> agg_fields;

  if(is_agg) {
    // is handle multi-table needed

    // collect query fields in `select` statement
    for(int i = static_cast<int>(select_sql.agg_funcs.size())-1; i >= 0; i--) {
      const AggFuncType func = select_sql.agg_funcs[i].func;
      const RelAttrSqlNode &relation_attr = select_sql.agg_funcs[i].attr;
      // handle empty field name 
      // select count() from t;
      // select count(*, num) from t;
      if(relation_attr.attribute_name.empty()) {
        return RC::BAD_AGG;  
      }

      // handle "*"
      if(0 == strcmp(relation_attr.attribute_name.c_str(), "*")) {
        if(func != AggFuncType::COUNT_FUNC) {
          return RC::BAD_AGG;
        }
        // '*'
        if(relation_attr.relation_name.empty()) {
          // count on first field of default table 
          agg_fields.push_back(agg_field(func, Field(nullptr, nullptr)));
          agg_fields.back().field_is_star = true;
        } else {
          // 't1.*'
          return RC::BAD_AGG;
        }
      } else  {
        // handle  *.rel
        if(relation_attr.relation_name == "*") {
          return RC::SCHEMA_FIELD_MISSING;
        } else if(relation_attr.relation_name == "") {
          // fix() select count(a) from t;
          // select count(a) from t1, t2; -> select count(t1.a), count(t2.a) from t1 join t2;
          


          for (Table *table : tables) {
              const FieldMeta * field_meta = table->table_meta().field(relation_attr.attribute_name.c_str());
              if(field_meta != nullptr) {
                agg_fields.push_back(SelectStmt::agg_field(func, Field(table,field_meta)));
              }
            // fix(lyq)
            // SELECT count(num) FROM aggregation_func;
            // wildcard_agg_fields(table, func, agg_fields);
          }
          if(agg_fields.empty()) {
            LOG_ERROR("no exist field");
            return RC::BAD_AGG;
          }


        } else {
          auto iter = table_map.find(relation_attr.relation_name);
          if(iter == table_map.end()) {
            return RC::SCHEMA_TABLE_NOT_EXIST;
          }
          Table* table = iter->second;

          const auto field_meta = table->table_meta().field(relation_attr.attribute_name.c_str());
          // avg semantic legal check, todo(lyq)
          // sum avg only on INTS and FLOATS
          // todo(lyq, recheck)
          if(func == AggFuncType::AVG_FUNC || func == AggFuncType::SUM_FUNC) {
            if(field_meta->type() != AttrType::INTS && field_meta->type() != AttrType::FLOATS) {
              LOG_ERROR("agg avg or sum on non-arithmetic attr");
              return RC::BAD_AGG;
            }
          }
          agg_fields.push_back(agg_field(func, Field(table, field_meta)));
        }
     }
    }
  }
  

  std::vector<Field> query_fields;
  // collect query fields in `select` statement

  for (int i = static_cast<int>(select_sql.attributes.size()) - 1; i >= 0; i--) {
    const RelAttrSqlNode &relation_attr = select_sql.attributes[i];

    if (common::is_blank(relation_attr.relation_name.c_str()) &&
        0 == strcmp(relation_attr.attribute_name.c_str(), "*")) {
      for (Table *table : tables) {
        wildcard_fields(table, query_fields);
      }

    } else if (!common::is_blank(relation_attr.relation_name.c_str())) {
      const char *table_name = relation_attr.relation_name.c_str();
      const char *field_name = relation_attr.attribute_name.c_str();

      if (0 == strcmp(table_name, "*")) {
        if (0 != strcmp(field_name, "*")) {
          LOG_WARN("invalid field name while table is *. attr=%s", field_name);
          return RC::SCHEMA_FIELD_MISSING;
        }
        for (Table *table : tables) {
          wildcard_fields(table, query_fields);
        }
      } else {
        auto iter = table_map.find(table_name);
        if (iter == table_map.end()) {
          LOG_WARN("no such table in from list: %s", table_name);
          return RC::SCHEMA_FIELD_MISSING;
        }

        Table *table = iter->second;
        if (0 == strcmp(field_name, "*")) {
          wildcard_fields(table, query_fields);
        } else {
          const FieldMeta *field_meta = table->table_meta().field(field_name);
          if (nullptr == field_meta) {
            LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), field_name);
            return RC::SCHEMA_FIELD_MISSING;
          }

          query_fields.push_back(Field(table, field_meta));
        }
      }
    } else {
      if (tables.size() != 1) {
        LOG_WARN("invalid. I do not know the attr's table. attr=%s", relation_attr.attribute_name.c_str());
        return RC::SCHEMA_FIELD_MISSING;
      }

      Table *table = tables[0];
      const FieldMeta *field_meta = table->table_meta().field(relation_attr.attribute_name.c_str());
      if (nullptr == field_meta) {
        LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), relation_attr.attribute_name.c_str());
        return RC::SCHEMA_FIELD_MISSING;
      }

      query_fields.push_back(Field(table, field_meta));
    }
  }

  LOG_INFO("got %d tables in from stmt and %d fields in query stmt", tables.size(), query_fields.size());



  // create filter statement in `where` statement
  FilterStmt *filter_stmt = nullptr;
  RC rc = FilterStmt::create(db,
      default_table,
      &table_map,
      select_sql.conditions.data(),
      static_cast<int>(select_sql.conditions.size()),
      filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot construct filter stmt");
    return rc;
  }

  // everything alright
  SelectStmt *select_stmt = new SelectStmt();
  // TODO add expression copy
  select_stmt->agg_fields_.swap(agg_fields);
  select_stmt->is_agg_ = is_agg;
  select_stmt->tables_.swap(tables);
  select_stmt->query_fields_.swap(query_fields);
  select_stmt->filter_stmt_ = filter_stmt;
  stmt = select_stmt;
  return RC::SUCCESS;
}
