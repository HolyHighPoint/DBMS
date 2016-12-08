#ifndef __USE_STATEMENT_H__
#define __USE_STATEMENT_H__

#include "SQLStatement.h"

namespace hsql
{
struct UseStatement : SQLStatement
{
    UseStatement(const char *name) :
        SQLStatement(kStmtUse),
        name(name) {}

    virtual ~UseStatement()
    {
        delete name;
    }

    const char *name;
};

} // namespace hsql
#endif
