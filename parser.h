#ifndef PARSER_H
#define PARSER_H

#include "rc.h"
#include "SQLParser.h"
#include "sql/SQLStatement.h"
#include "sql/statements.h"
#include "sm_manager.h"

namespace hsql
{

RC parseCreateStatement(CreateStatement *stmt)
{
    SM_Manager *sm = SM_Manager::getInstance();

    if (stmt->type == CreateStatement::kDatabase)
    {
        return sm->createDatabase(stmt->tableName);
    }

    if (stmt->type == CreateStatement::kTable)
    {
        return sm->createTable(stmt->tableName, *stmt->columns);
    }
}

RC parseDropStatement(DropStatement *stmt)
{
    SM_Manager *sm = SM_Manager::getInstance();

    if (stmt->type == DropStatement::kDatabase)
    {
        return sm->dropDatabase(stmt->name);
    }
    else if (stmt->type == DropStatement::kTable)
    {
        return sm->dropTable(stmt->name);
    }
}

RC parseUseStatement(UseStatement *stmt)
{
    SM_Manager *sm = SM_Manager::getInstance();
    return sm->useDatabase(stmt->name);
}

RC parseShowStatement(ShowStatement *stmt)
{
    SM_Manager *sm = SM_Manager::getInstance();

    if (stmt->type == ShowStatement::kDatabase)
    {
        return sm->showDatabases();
    }
    else if (stmt->type == ShowStatement::kTable)
    {
        return sm->showTables();
    }
}

RC parseDescStatement(DescStatement *stmt)
{
    SM_Manager *sm = SM_Manager::getInstance();
    return sm->descTable(stmt->name);
}

RC parseStatement(SQLStatement *stmt)
{
    switch (stmt->type())
    {
        case kStmtCreate:
            return parseCreateStatement((CreateStatement *) stmt);
            break;

        case kStmtDrop:
            return parseDropStatement((DropStatement *) stmt);
            break;

        case kStmtUse:
            return parseUseStatement((UseStatement *) stmt);
            break;

        case kStmtShow:
            return parseShowStatement((ShowStatement *) stmt);
            break;

        case kStmtDesc:
            return parseDescStatement((DescStatement *) stmt);
            break;

        default:
            break;
    }
}
}

#endif
