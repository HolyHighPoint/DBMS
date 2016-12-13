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
    else if (stmt->type == CreateStatement::kTable)
    {
        return sm->createTable(stmt->tableName, *stmt->columns);
    }
    else if (stmt->type == CreateStatement::kIndex)
    {
        return sm->createIndex(stmt->tableName, stmt->indexName);
    }

    return Error;
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
    else if (stmt->type == DropStatement::kIndex)
    {
        return sm->dropIndex(stmt->name, stmt->index);
    }

    return Error;
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

    return Error;
}

RC parseDescStatement(DescStatement *stmt)
{
    SM_Manager *sm = SM_Manager::getInstance();
    return sm->descTable(stmt->name);
}

RC parseInsertStatement(InsertStatement *stmt)
{
    SM_Manager *sm = SM_Manager::getInstance();
    RC result = Success;

    for (auto vec : *stmt->values)
    {
        if (sm->insertRecord(stmt->tableName, *vec) == Error) result = Error;
    }

    return result;
}

RC parseDeleteStatement(DeleteStatement *stmt)
{
    SM_Manager *sm = SM_Manager::getInstance();
    return sm->deleteRecord(stmt->tableName, stmt->expr);
}

RC parseSelectStatement(SelectStatement *stmt)
{
    SM_Manager *sm = SM_Manager::getInstance();

    if (stmt->fromTable->type == kTableName)
        return sm->selectRecord(stmt->fromTable->name, *stmt->selectList, stmt->whereClause);
    else
        return Error;
}

RC parseUpdateStatement(UpdateStatement *stmt)
{
    SM_Manager *sm = SM_Manager::getInstance();
    return sm->updateRecord(stmt->table->name, *stmt->updates, stmt->where);
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

        case kStmtInsert:
            return parseInsertStatement((InsertStatement *) stmt);
            break;

        case kStmtSelect:
            return parseSelectStatement((SelectStatement *) stmt);
            break;

        case kStmtDelete:
            return parseDeleteStatement((DeleteStatement *) stmt);
            break;

        case kStmtUpdate:
            return parseUpdateStatement((UpdateStatement *) stmt);
            break;


        default:
            break;
    }
}
}

#endif
