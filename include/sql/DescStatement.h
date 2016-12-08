#ifndef __DESC_STATEMENT_H__
#define __DESC_STATEMENT_H__

#include "SQLStatement.h"

namespace hsql
{
struct DescStatement : SQLStatement
{
    DescStatement(const char *name) :
        SQLStatement(kStmtDesc),
        name(name) {}

    virtual ~DescStatement()
    {
        delete name;
    }

    const char *name;
};

} // namespace hsql
#endif
