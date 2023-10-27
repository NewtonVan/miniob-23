#include "sql/stmt/single_table_stmt.h"
#include "common/log/log.h"
#include "common/rc.h"
#include "sql/parser/parse_defs.h"
#include "storage/db/db.h"
#include "storage/field/field.h"
#include <cstring>
#include <vector>

RC SingleTableStmt::create(Db *db, std::vector<Field> &all_fields, GeneralRelationSqlNode *rel, Stmt *&stmt)
{
  if (rel->type != REL_TABLE) {
    return RC::INTERNAL;
  }
  std::string        table_name = std::get<std::string>(rel->relation);
  std::vector<Field> query_fields;
  for (const Field &field : all_fields) {
    if (0 == strcmp(field.table_name(), table_name.c_str())) {
      query_fields.push_back(field);
    }
  }

  SingleTableStmt *table = new SingleTableStmt();
  table->table_name_     = table_name;
  table->table_          = db->find_table(table_name.c_str());
  table->query_fields_.swap(query_fields);

  if (table->table_ == nullptr) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name.c_str());
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  stmt = table;

  return RC::SUCCESS;
}