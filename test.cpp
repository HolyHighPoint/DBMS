#include <iostream>
#include <string>
#include "SQLParser.h"
#include "rc.h"
#include "parser.h"

using namespace std;
int main(int argc, char *argv[])
{
    if (argc > 1)freopen(argv[1], "r", stdin);

    char buf[1024];
    string query;

    while (scanf("%s", buf) != EOF)
    {
        query = query + " " + buf;
    }

    hsql::SQLParserResult *result = hsql::SQLParser::parseSQLString(query);

    if (result->isValid)
    {
        for (hsql::SQLStatement * stmt : result->statements)
        {
            // process the statements...
            RC result = parseStatement(stmt);
        }
    }
    else
    {
        printf("line: %d, column: %d\n", result->errorLine, result->errorColumn);
        printf("%s\n", result->errorMsg);
    }

    return 0;
}
