#include "sql/Expr.h"
#include <stdio.h>
#include <string.h>
#include <string>
using namespace std;

namespace hsql
{

char *substr(const char *source, int from, int to)
{
    int len = to - from;
    char *copy = new char[len + 1];
    strncpy(copy, source + from, len);
    copy[len] = '\0';
    return copy;
}




Expr *Expr::makeOpUnary(OperatorType op, Expr *expr)
{
    Expr *e = new Expr(kExprOperator);
    e->op_type = op;
    e->expr = expr;
    e->expr2 = NULL;
    return e;
}



Expr *Expr::makeOpBinary(Expr *expr1, OperatorType op, Expr *expr2)
{
    Expr *e = new Expr(kExprOperator);
    e->op_type = op;
    e->op_char = 0;
    e->expr = expr1;
    e->expr2 = expr2;
    return e;
}

Expr *Expr::makeOpBinary(Expr *expr1, char op, Expr *expr2)
{
    Expr *e = new Expr(kExprOperator);
    e->op_type = SIMPLE_OP;
    e->op_char = op;
    e->expr = expr1;
    e->expr2 = expr2;
    return e;
}



Expr *Expr::makeLiteral(int64_t val)
{
    Expr *e = new Expr(kExprLiteralInt);
    e->ival = val;
    return e;
}

Expr *Expr::makeLiteral(double value)
{
    Expr *e = new Expr(kExprLiteralFloat);
    e->fval = value;
    return e;
}

Expr *Expr::makeLiteral(char *string)
{
    Expr *e = new Expr(kExprLiteralString);
    e->name = string;
    return e;
}

Expr *Expr::makeLiteral()
{
    Expr *e = new Expr(kExprLiteralNull);
    return e;
}


Expr *Expr::makeColumnRef(char *name)
{
    Expr *e = new Expr(kExprColumnRef);
    e->name = name;
    return e;
}

Expr *Expr::makeColumnRef(char *table, char *name)
{
    Expr *e = new Expr(kExprColumnRef);
    e->name = name;
    e->table = table;
    return e;
}

Expr *Expr::makeFunctionRef(char *func_name, Expr *expr, bool distinct)
{
    Expr *e = new Expr(kExprFunctionRef);
    e->name = func_name;
    e->expr = expr;
    e->distinct = distinct;
    return e;
}

Expr *Expr::makePlaceholder(int id)
{
    Expr *e = new Expr(kExprPlaceholder);
    e->ival = id;
    return e;
}

string Expr::toString()
{
    char buf[1024];

    switch (type)
    {
        case kExprStar:
            return "*";

        case kExprColumnRef:
            return name;

        case kExprLiteralFloat:
            sprintf(buf, "%lf", fval);
            return buf;

        case kExprLiteralInt:
            sprintf(buf, "%ld", ival);
            return buf;

        case kExprLiteralString:
            sprintf(buf, "\'%s\'", name);
            return buf;

        case kExprFunctionRef:
            sprintf(buf, "%s ( %s )", name, expr->name);
            return buf;

        case kExprOperator:
        {
            string left, right;

            if (expr)left = expr->toString();

            if (expr2)right = expr2->toString();

            switch (op_type)
            {
                case Expr::SIMPLE_OP:
                    sprintf(buf, "( %s ) %c ( %s )", left.c_str(), op_char, right.c_str());
                    return buf;

                case Expr::AND:
                    sprintf(buf, "( %s ) AND ( %s )", left.c_str(), right.c_str());
                    return buf;

                case Expr::OR:
                    sprintf(buf, "( %s ) OR ( %s )", left.c_str(), right.c_str());
                    return buf;

                case Expr::NOT:
                    sprintf(buf, "NOT ( %s )", left.c_str());
                    return buf;
            }
        }

        default:
            return "";
    }
}

Expr::~Expr()
{
    delete expr;
    delete expr2;
    delete name;
    delete table;
}

} // namespace hsql
