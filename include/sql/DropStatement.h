#ifndef __DROP_STATEMENT_H__
#define __DROP_STATEMENT_H__

#include "SQLStatement.h"

namespace hsql
{
/**
 * Represents SQL Delete statements.
 * Example "DROP TABLE students;"
 */
struct DropStatement : SQLStatement
{
    enum EntityType
    {
        kTable,
        kSchema,
        kIndex,
        kView,
        kPreparedStatement,
        kDatabase
    };

    DropStatement(EntityType type) :
        SQLStatement(kStmtDrop),
        type(type),
        name(NULL),
        index(NULL) {}

    virtual ~DropStatement()
    {
        delete name;
        delete index;
    }

    EntityType type;
    const char *name;
    const char *index;
};

} // namespace hsql
#endif
