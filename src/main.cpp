#include <iostream>
#include <fstream>
#include <string>
#include "SQLParser.h"
#include "rc.h"
#include "parser.h"

using namespace std;
int main(int argc, char *argv[])
{
    string query, usequery;

    if (argc > 1)
    {
        if (!freopen(argv[1], "r", stdin))
        {
            query = string(argv[1]);
        }
    }

    if (query.empty())query = string((istreambuf_iterator<char>(cin)), istreambuf_iterator<char>());

    if (argc > 2)
    {
        usequery = "USE DATABASE " + string(argv[2]) + ";";
        hsql::SQLParserResult *result = hsql::SQLParser::parseSQLString(usequery);

        if (result->isValid)for (hsql::SQLStatement * stmt : result->statements)
            {
                RC result = parseStatement(stmt);
            }
    }

    for (int i = 0; i < query.length(); i++)if (query[i] == '\r')query[i] = ' ';

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
        fprintf(stderr, "line: %d, column: %d\n", result->errorLine + 1, result->errorColumn + 1);
        fprintf(stderr, "%s\n", result->errorMsg);
    }

    return 0;
}
