#ifndef __CREATE_STATEMENT_H__
#define __CREATE_STATEMENT_H__

#include "SQLStatement.h"
#include "Expr.h"

namespace hsql
{
/**
 * Represents definition of a table column
 */
struct ColumnDefinition
{
    enum DataType
    {
        INT,
        INTEGER,
        TINYINT,
        CHAR,
        VARCHAR,
        PRIMARY,
        CHECK
    };

    ColumnDefinition(char *name, DataType type, bool notnull, int64_t len = 0) :
        name(name),
        type(type),
        notnull(notnull),
        len(len),
        expr(NULL) {}

    ColumnDefinition(Expr *expr, DataType type) :
        name(NULL),
        type(type),
        notnull(false),
        len(0),
        expr(expr) {}

    virtual ~ColumnDefinition()
    {
        if (name) delete name;

        if (expr) delete expr;
    }

    char *name;
    DataType type;
    bool notnull;
    int64_t len;
    Expr *expr;
};

/**
 * Represents SQL Create statements.
 * Example: "CREATE TABLE students (name TEXT, student_number INTEGER, city TEXT, grade DOUBLE)"
 */
struct CreateStatement : SQLStatement
{
    enum CreateType
    {
        kTable,
        kTableFromTbl, // Hyrise file format
        kDatabase,
        kIndex
    };

    CreateStatement(CreateType type) :
        SQLStatement(kStmtCreate),
        type(type),
        ifNotExists(false),
        filePath(NULL),
        tableName(NULL),
        indexName(NULL),
        columns(NULL) {};

    virtual ~CreateStatement()
    {
        delete columns;
        delete filePath;
        delete tableName;
        delete indexName;
    }

    CreateType type;

    bool ifNotExists;
    const char *filePath;
    const char *tableName;
    const char *indexName;
    std::vector<ColumnDefinition *> *columns;
};

} // namespace hsql
#endif
