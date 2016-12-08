#ifndef __SHOW_STATEMENT_H__
#define __SHOW_STATEMENT_H__

#include "SQLStatement.h"

namespace hsql
{
struct ShowStatement : SQLStatement
{
    enum EntityType
    {
        kTable,
        kDatabase
    };

    ShowStatement(EntityType type) :
        SQLStatement(kStmtShow),
        type(type)
    {
    }

    virtual ~ShowStatement()
    {
    }

    EntityType type;
};

} // namespace hsql
#endif
