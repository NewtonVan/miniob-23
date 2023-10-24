#pragma once

#include "common/rc.h"

class SQLStageEvent;

/**
 * @brief drop table
 * @ingroup Executor
 */
class DropTableExecutor
{
public:
  DropTableExecutor()          = default;
  virtual ~DropTableExecutor() = default;

  RC execute(SQLStageEvent *sql_event);
};