#ifndef TM_MANAGER_H
#define TM_MANAGER_H
#include "rc.h"
#include <boost/filesystem.hpp>
#include <fstream>
#include <map>
#include "sql/statements.h"
#include "rm_filehandle.h"
#include "rm_manager.h"
#include "rm_record.h"
#include "ix_manager.h"

namespace bf = boost::filesystem;

class TM_Manager
{
private:
    RM_Manager *rmm;
    bf::path path;
public:
    RM_FileHandle *rmfh;
    std::map<std::string, IX_Manager *> indexst;
    std::vector<IX_Manager *> indexv;
    TM_Manager(FileManager *fm, BufPageManager *bpm, bf::path path)
        : path(path)
    {
        rmm = new RM_Manager(fm, bpm);
        rmfh = new RM_FileHandle(path);
        bool exists = boost::filesystem::exists(path / "data.db");
        rmm->CreateFile((path / "data.db").string().c_str());
        rmm->OpenFile((path / "data.db").string().c_str(), rmfh, !exists);
        createIndex();
    }

    ~TM_Manager()
    {
        rmm->CloseFile(rmfh);
        delete rmfh;
        delete rmm;

        for (auto it : indexst)
            delete it.second;
    }

    RC createIndex(bool createNew = false)
    {
        indexv.clear();
        std::vector<std::pair<RID, RM_Record> > alldata;

        if (createNew)alldata = rmfh->ListRec();

        bf::path filename = path / configFile;
        std::ifstream fi(filename.string());
        int n;
        fi >> n;

        for (int i = 0; i < n; i++)
        {
            std::string name, type;
            bool notnull, index, primary;
            int len;
            getline(fi, name);

            if (name.empty())getline(fi, name);

            fi >> type >> len >> notnull >> index >> primary;
            Type *data;

            if (type == "INTEGER")
            {
                data = Type::make(!notnull, 0, -1);
            }
            else if (type == "INT")
            {
                data = Type::make(!notnull, 0, len);
            }
            else if (type == "CHAR" || type == "VARCHAR")
            {
                data = Type::make(!notnull, "", len);
            }

            if (index && indexst.find(name) == indexst.end())
            {
                bf::path f1 = path / ("_" + name + ".db");
                bf::path f2 = path / ("_deque_" + name + ".db");
                IX_Manager *it = new IX_Manager(f1.c_str(), primary ? NULL : f2.c_str(), data);
                indexst.insert(make_pair(name, it));

                for (auto data : alldata)
                {
                    it->InsertEntry(data.second.get(i), data.first);
                }
            }

            auto it = indexst.find(name);
            indexv.push_back(it == indexst.end() ? NULL : it->second);
        }

        for (auto it : alldata)
        {
            it.second.clear();
        }

        return Success;
    }

    RC dropIndex()
    {
        indexv.clear();
        bf::path filename = path / configFile;
        std::ifstream fi(filename.string());
        int n;
        fi >> n;

        for (int i = 0; i < n; i++)
        {
            std::string name, type;
            bool notnull, index, primary;
            int len;
            getline(fi, name);

            if (name.empty())getline(fi, name);

            fi >> type >> len >> notnull >> index >> primary;

            auto it = indexst.find(name);

            if (!index && it != indexst.end())
            {
                delete it->second;
                bf::path f1 = path / ("_" + name + ".db");
                bf::path f2 = path / ("deque_" + name + ".db");
                bf::remove(f1);

                if (!primary)bf::remove(f2);

                indexst.erase(it);
            }

            it = indexst.find(name);
            indexv.push_back(it == indexst.end() ? NULL : it->second);
        }

        return Success;
    }

    std::map<string, int> makeHeadMap()
    {
        bf::path filename = path / configFile;
        std::ifstream fi(filename.string());
        int n;
        fi >> n;
        std::map<string, int>st;

        for (int i = 0; i < n; i++)
        {
            std::string name, type;
            bool notnull, index, primary;
            int len;
            getline(fi, name);

            if (name.empty())getline(fi, name);

            fi >> type >> len >> notnull >> index >> primary;
            st[name] = i;
        }

        return st;
    }

    RC insertRecord(std::vector<hsql::Expr *> values)
    {

        bf::path filename = path / configFile;
        std::ifstream fi(filename.string());
        int n, m;
        fi >> n;

        if (n != int(values.size()))
        {
            fprintf(stderr, "There are %d columns in this table but insert %d columns\n", n, int(values.size()));
            return Error;
        }

        RM_Record head;


        for (int i = 0; i < n; i++)
        {
            std::string name, type;
            bool notnull, index, primary;
            int len;
            getline(fi, name);

            if (name.empty())getline(fi, name);

            fi >> type >> len >> notnull >> index >> primary;
            Type *data;

            switch (values[i]->type)
            {
                case hsql::kExprLiteralInt:
                    if (type == "INTEGER" || type == "INT")
                    {
                        data = Type::make(false, values[i]->ival, len);
                    }
                    else
                    {
                        fprintf(stderr, "Values[%d] type is error.\n", i);
                        return Error;
                    }

                    break;

                case hsql::kExprLiteralString:
                    if (type == "CHAR" || type == "VARCHAR")
                    {
                        if (strlen(values[i]->name) > len)
                        {
                            fprintf(stderr, "Values[%d] '%s' is longer than %d.\n", i, values[i]->name, len);
                            return Error;
                        }

                        data = Type::make(false, values[i]->name, len);

                    }
                    else
                    {
                        fprintf(stderr, "Values[%d] type is error.\n", i);
                        return Error;
                    }

                    break;

                case hsql::kExprLiteralNull:
                    if (notnull)
                    {
                        fprintf(stderr, "Values[%d] can't be null.\n", i);
                        return Error;
                    }

                    if (type == "INTEGER" || type == "INT")
                    {
                        data = Type::make(true, 0, len);
                    }
                    else if (type == "CHAR" || type == "VARCHAR")
                    {
                        data = Type::make(true, "", 0);
                    }
                    else
                    {
                        fprintf(stderr, "Values[%d] type is error.\n", i);
                        return Error;
                    }

                    break;

                default:
                    fprintf(stderr, "Values[%d] type is error.\n", i);
                    return Error;
            }

            if (primary)
            {
                std::vector<RID> check = indexv[i]->SearchEntry(data);

                if (!check.empty())
                {
                    fprintf(stderr, "Values[%d] is a Primary Key and unique.\n", i);
                    return Error;
                }
            }

            head.push_back(data);
        }

        fi >> m;
        vector<hsql::Expr *> checks;

        for (int i = 0; i < m; i++)
        {
            std::string expr;
            getline(fi, expr);

            if (expr.empty())getline(fi, expr);

            hsql::SQLParserResult *result = hsql::SQLParser::parseSQLString(expr);

            if (result->isValid)
            {
                for (hsql::SQLStatement * stmt : result->statements)
                {
                    if (stmt->type() == hsql::kStmtSelect)
                    {
                        checks.push_back(((hsql::SelectStatement *)stmt)->whereClause);
                    }
                    else
                    {
                        fprintf(stderr, "Check expr is error\n");
                        return Error;
                    }
                }
            }
            else
            {
                fprintf(stderr, "Check expr is error\n");
                return Error;
            }
        }


        std::map<string, int> st = makeHeadMap();

        for (hsql::Expr * expr : checks)
        {
            bool flag;

            if (expr && check(*expr, st, head, flag) == Error)return Error;

            if (!flag)
            {
                fprintf(stderr, "Check exprs equal false\n");
                return Error;
            }
        }

        RID rid;
        RC result = rmfh->InsertRec(head, rid);

        for (int i = 0; i < indexv.size(); i++)if (indexv[i])indexv[i]->InsertEntry(head.get(i), rid);

        head.clear();
        return result;

    }

    RC check(const hsql::Expr &expr, const std::map<string, int> &st, RM_Record &rec, bool &flag)
    {
        if (expr.type != hsql::kExprOperator)
        {
            fprintf(stderr, "Where Expr should be a bool expression.\n");
            return Error;
        }

        int tleft = 0;
        int ileft;
        const char *cleft;
        bool bleft;

        switch (expr.expr->type)
        {
            case hsql::kExprColumnRef:
            {
                auto it = st.find(std::string(expr.expr->name));

                if (it == st.end())
                {
                    fprintf(stderr, "Column %s is not found.\n", expr.expr->name);
                    return Error;
                }

                Type *t = rec.get(it->second);

                if (t->null)
                {
                    tleft = 3;
                }
                else if (t->isInt())
                {
                    tleft = 0;
                    ileft = t->getValue();
                }
                else if (t->isStr())
                {
                    tleft = 1;
                    cleft = t->getStr();
                }
                else
                {
                    fprintf(stderr, "The Expr Column Type is error.\n");
                    return Error;
                }
            }
            break;

            case hsql::kExprLiteralInt:
                tleft = 0;
                ileft = expr.expr->ival;
                break;

            case hsql::kExprLiteralString:
                tleft = 1;
                cleft = expr.expr->name;
                break;

            case hsql::kExprOperator:
                tleft = 2;
                check(*expr.expr, st, rec, bleft);
                break;

            case hsql::kExprLiteralNull:
                tleft = 3;
                break;

            default:
                fprintf(stderr, "The Expr Literal Type is error.\n");
                return Error;
        }

        if (expr.op_type == hsql::Expr::NOT)
        {
            if (tleft == 2)
            {
                flag = !bleft;
                return Success;
            }
            else
            {
                fprintf(stderr, "The Expr Type is error.\n");
                return Error;
            }
        }

        int tright = 0;
        int iright;
        const char *cright;
        bool bright;

        switch (expr.expr2->type)
        {
            case hsql::kExprColumnRef:
            {
                auto it = st.find(std::string(expr.expr2->name));

                if (it == st.end())
                {
                    fprintf(stderr, "Column %s is not found.\n", expr.expr2->name);
                    return Error;
                }

                Type *t = rec.get(it->second);

                if (t->null)
                {
                    tright = 3;
                }
                else if (t->isInt())
                {
                    tright = 0;
                    iright = t->getValue();
                }
                else if (t->isStr())
                {
                    tright = 1;
                    cright = t->getStr();
                }
                else
                {
                    fprintf(stderr, "The Expr Column Type is error.\n");
                    return Error;
                }
            }
            break;

            case hsql::kExprLiteralInt:
                tright = 0;
                iright = expr.expr2->ival;
                break;

            case hsql::kExprLiteralString:
                tright = 1;
                cright = expr.expr2->name;
                break;

            case hsql::kExprOperator:
                tright = 2;
                check(*expr.expr2, st, rec, bright);
                break;

            case hsql::kExprLiteralNull:
                tright = 3;
                break;

            default:
                fprintf(stderr, "The Expr Literal Type is error.\n");
                return Error;
        }

        if ((tleft != 3 && tright == 3) || (tleft == 3 && tright != 3))
        {
            flag = false;
            return Success;
        }

        if (tleft != tright)
        {
            fprintf(stderr, "The Expr Type is error.\n");
            return Error;
        }

        switch (expr.op_type)
        {
            case hsql::Expr::SIMPLE_OP:

                if (expr.op_char == '=')
                {
                    if (tleft == 0)
                        flag = (ileft == iright);
                    else if (tleft == 1)
                        flag = (strcmp(cleft, cright) == 0);
                    else if (tleft == 3)
                        flag = true;
                    else
                    {
                        fprintf(stderr, "The Expr Type is error.\n");
                        return Error;
                    }
                }
                else if (expr.op_char == '<')
                {
                    if (tleft == 0)
                        flag = (ileft < iright);
                    else if (tleft == 1)
                        flag = (strcmp(cleft, cright) < 0);
                    else
                    {
                        fprintf(stderr, "The Expr Type is error.\n");
                        return Error;
                    }
                }
                else if (expr.op_char == '>')
                {
                    if (tleft == 0)
                        flag = (ileft > iright);
                    else if (tleft == 1)
                        flag = (strcmp(cleft, cright) > 0);
                    else
                    {
                        fprintf(stderr, "The Expr Type is error.\n");
                        return Error;
                    }
                }

                break;

            case hsql::Expr::NOT_EQUALS:
                if (tleft == 0)
                    flag = (ileft != iright);
                else if (tleft == 1)
                    flag = (strcmp(cleft, cright) != 0);
                else
                {
                    fprintf(stderr, "The Expr Type is error.\n");
                    return Error;
                }

                break;

            case hsql::Expr::LESS_EQ:
                if (tleft == 0)
                    flag = (ileft <= iright);
                else if (tleft == 1)
                    flag = (strcmp(cleft, cright) <= 0);
                else
                {
                    fprintf(stderr, "The Expr Type is error.\n");
                    return Error;
                }

                break;

            case hsql::Expr::GREATER_EQ:
                if (tleft == 0)
                    flag = (ileft >= iright);
                else if (tleft == 1)
                    flag = (strcmp(cleft, cright) >= 0);
                else
                {
                    fprintf(stderr, "The Expr Type is error.\n");
                    return Error;
                }

                break;

            case hsql::Expr::AND:
                if (tleft == 2)
                    flag = (bleft && bright);
                else
                {
                    fprintf(stderr, "The Expr Type is error.\n");
                    return Error;
                }

                break;

            case hsql::Expr::OR:
                if (tleft == 2)
                    flag = (bleft || bright);
                else
                {
                    fprintf(stderr, "The Expr Type is error.\n");
                    return Error;
                }

                break;

                //        case hsql::Expr::NOT:
                //            break;
            default:
                fprintf(stderr, "The Expr Operation is error.\n");
                return Error;
                break;
        }

        return Success;

    }

    RC getSet(const hsql::Expr &expr, const std::map<string, int> &st, std::map<RID, RM_Record> &ans, bool &flag)
    {
        if (expr.type != hsql::kExprOperator)
        {
            fprintf(stderr, "Where Expr should be a bool expression.\n");
            return Error;
        }

        int tleft = 0;
        std::map<RID, RM_Record> sleft;
        RM_Record head = rmfh->makeHead();
        Type *data;
        IX_Manager *index;

        switch (expr.expr->type)
        {
            case hsql::kExprColumnRef:
            {
                auto it = st.find(std::string(expr.expr->name));

                if (it == st.end())
                {
                    fprintf(stderr, "Column %s is not found.\n", expr.expr->name);
                    return Error;
                }

                data = head.get(it->second);

                if ((index = indexv[it->second]) == NULL)
                {
                    fprintf(stderr, "Column %s doesn't have index and try to use brute-force...\n", expr.expr->name);
                    flag = false;
                    return Success;
                }
            }
            break;

            case hsql::kExprOperator:
            {
                tleft = 1;
                bool f;
                RC result = getSet(*expr.expr, st, sleft, f);

                if (result == Error)
                {
                    return Error;
                }
                else if (f == false)
                {
                    flag = false;
                    return Success;
                }
            }
            break;

            default:
                fprintf(stderr, "Try to use brute-force...\n");
                flag = false;
                return Success;
        }

        if (expr.op_type == hsql::Expr::NOT)
        {
            fprintf(stderr, "Try to use brute-force...\n");
            flag = false;
            return Success;
        }

        int tright;
        std::map<RID, RM_Record> sright;
        int iright;
        const char *cright;

        switch (expr.expr2->type)
        {
            case hsql::kExprColumnRef:
                fprintf(stderr, "Try to use brute-force...\n");
                flag = false;
                return Success;

            case hsql::kExprLiteralInt:
                tright = 2;
                iright = expr.expr2->ival;
                break;

            case hsql::kExprLiteralString:
                tright = 3;
                cright = expr.expr2->name;
                break;

            case hsql::kExprLiteralNull:
                tright = 4;
                break;

            case hsql::kExprOperator:
            {
                tright = 1;
                bool f;
                RC result = getSet(*expr.expr2, st, sright, f);

                if (result == Error)
                {
                    return Error;
                }
                else if (f == false)
                {
                    flag = false;
                    return Success;
                }
            }
            break;

            default:
                fprintf(stderr, "Try to use brute-force...\n");
                flag = false;
                return Success;
        }



        if (tleft == tright && tleft == 1)
        {
            switch (expr.op_type)
            {
                case hsql::Expr::AND:
                    for (auto it : sleft)
                    {
                        if (sright.find(it.first) != sright.end())
                            ans.insert(it);
                    }

                    flag = true;
                    break;

                case hsql::Expr::OR:
                    for (auto it : sleft)
                    {
                        if (ans.find(it.first) == ans.end())
                            ans.insert(it);
                    }

                    for (auto it : sright)
                    {
                        if (ans.find(it.first) == ans.end())
                            ans.insert(it);
                    }

                    flag = true;

                    break;

                default:
                    fprintf(stderr, "The Expr Operation is error.\n");
                    return Error;
            }
        }
        else if (tleft == 0 && tright == 2)
        {
            if (!data->set(iright))
            {
                fprintf(stderr, "The Expr Column Type is error.\n");
                return Error;
            }

            switch (expr.op_type)
            {
                case hsql::Expr::SIMPLE_OP:

                    if (expr.op_char == '=')
                    {
                        std::vector<RID> vec = index->SearchEntry(data);

                        for (auto rid : vec)
                        {
                            RM_Record rec;
                            rmfh->GetRec(rid, rec);
                            ans.insert(make_pair(rid, rec));
                        }
                    }

                    else if (expr.op_char == '<')
                    {
                        Type *t = new Type_int(false, 0x80000000);
                        std::vector<RID> vec = index->SearchRangeEntry(t, data);
                        auto it = st.find(std::string(expr.expr->name));

                        for (auto rid : vec)
                        {
                            RM_Record rec;
                            rmfh->GetRec(rid, rec);

                            if (*((Type_int *)rec.get(it->second)) == *(Type_int *)data)
                            {
                                rec.clear();
                                continue;
                            }

                            ans.insert(make_pair(rid, rec));
                        }
                    }
                    else if (expr.op_char == '>')
                    {
                        Type *t = new Type_int(false, 0x7fffffff);
                        std::vector<RID> vec = index->SearchRangeEntry(data, t);
                        auto it = st.find(std::string(expr.expr->name));

                        for (auto rid : vec)
                        {
                            RM_Record rec;
                            rmfh->GetRec(rid, rec);

                            if (*((Type_int *)rec.get(it->second)) == *(Type_int *)data)
                            {
                                rec.clear();
                                continue;
                            }

                            ans.insert(make_pair(rid, rec));
                        }
                    }

                    break;

                case hsql::Expr::LESS_EQ:
                {
                    Type *t = new Type_int(false, 0x80000000);
                    std::vector<RID> vec = index->SearchRangeEntry(t, data);
                    auto it = st.find(std::string(expr.expr->name));

                    for (auto rid : vec)
                    {
                        RM_Record rec;
                        rmfh->GetRec(rid, rec);
                        ans.insert(make_pair(rid, rec));
                    }
                }
                break;

                case hsql::Expr::GREATER_EQ:
                {
                    Type *t = new Type_int(false, 0x7fffffff);
                    std::vector<RID> vec = index->SearchRangeEntry(data, t);
                    auto it = st.find(std::string(expr.expr->name));

                    for (auto rid : vec)
                    {
                        RM_Record rec;
                        rmfh->GetRec(rid, rec);
                        ans.insert(make_pair(rid, rec));
                    }
                }
                break;

                default:
                    fprintf(stderr, "Try to use brute-force...\n");
                    flag = false;
                    return Success;
            }
        }
        else if (tleft == 0 && tright == 3)
        {
            if (!data->set(cright, strlen(cright)))
            {
                fprintf(stderr, "The Expr Column Type is error.\n");
                return Error;
            }

            switch (expr.op_type)
            {
                case hsql::Expr::SIMPLE_OP:
                    if (expr.op_char == '=')
                    {
                        std::vector<RID> vec = index->SearchEntry(data);

                        for (auto rid : vec)
                        {
                            RM_Record rec;
                            rmfh->GetRec(rid, rec);
                            ans.insert(make_pair(rid, rec));
                        }
                    }

                    break;

                default:
                    fprintf(stderr, "Try to use brute-force...\n");
                    flag = false;
                    return Success;
            }
        }
        else if (tleft == 0 && tright == 4)
        {
            data->setnull();

            switch (expr.op_type)
            {
                case hsql::Expr::SIMPLE_OP:
                    if (expr.op_char == '=')
                    {
                        std::vector<RID> vec = index->SearchEntry(data);

                        for (auto rid : vec)
                        {
                            RM_Record rec;
                            rmfh->GetRec(rid, rec);
                            ans.insert(make_pair(rid, rec));
                        }
                    }

                    break;

                default:
                    fprintf(stderr, "Try to use brute-force...\n");
                    flag = false;
                    return Success;
            }
        }
        else
        {
            fprintf(stderr, "The Expr Type is error.\n");
            return Error;
        }

        flag = true;
        return Success;

    }

    RC selectRecord(std::vector<hsql::Expr *> &fields, hsql::Expr *wheres)
    {
        std::map<string, int> st = makeHeadMap();
        std::vector<RM_Record> ans;
        bool flag = false;
        std::map<RID, RM_Record> set;
        std::vector<std::pair<RID, RM_Record> > data;

        if (wheres && getSet(*wheres, st, set, flag) == Error)return Error;

        if (flag)
        {
            for (auto it : set)
            {
                data.push_back(it);
                ans.push_back(it.second);
            }
        }
        else
        {
            data = rmfh->ListRec();

            for (auto it : data)
            {
                bool flag;

                if (wheres && check(*wheres, st, it.second, flag) == Error)
                {
                    return Error;
                }

                if (!wheres || flag)ans.push_back(it.second);
            }
        }

        std::map<std::string, int>mi, ma, num;
        std::map<std::string, long long>sum;
        bool func = false;

        for (RM_Record rec : ans)
        {
            for (hsql::Expr * expr : fields)
            {
                switch (expr->type)
                {
                    case hsql::kExprStar:
                        rec.print();
                        break;

                    case hsql::kExprColumnRef:
                    {
                        auto it = st.find(std::string(expr->name));

                        if (it == st.end())
                        {
                            fprintf(stderr, "Column %s is not found.\n", expr->name);
                            return Error;
                        }

                        Type *t = rec.get(it->second);
                        t->print();
                    }
                    break;

                    case hsql::kExprFunctionRef:
                    {
                        func = true;
                        auto it = st.find(std::string(expr->expr->name));

                        if (it == st.end())
                        {
                            fprintf(stderr, "Column %s is not found.\n", expr->expr->name);
                            return Error;
                        }

                        Type *t = rec.get(it->second);
                        t->print();

                        if (dynamic_cast<Type_int *>(t) == NULL)
                        {
                            fprintf(stderr, "Column %s is not a integer.\n", expr->expr->name);
                            return Error;
                        }

                        sum[std::string(expr->expr->name)] += ((Type_int *)t)->getValue();
                        num[std::string(expr->expr->name)] ++;

                        if ((it = ma.find(std::string(expr->expr->name))) == ma.end())
                            ma.insert(make_pair(std::string(expr->expr->name), ((Type_int *)t)->getValue()));
                        else
                            it->second = std::max(it->second, ((Type_int *)t)->getValue());

                        if ((it = mi.find(std::string(expr->expr->name))) == mi.end())
                            mi.insert(make_pair(std::string(expr->expr->name), ((Type_int *)t)->getValue()));
                        else
                            it->second = std::min(it->second, ((Type_int *)t)->getValue());
                    }
                    break;

                    default:
                        fprintf(stderr, "Expr type is error.\n");
                        return Error;
                }
            }

            printf("\n");
        }

        if (func)
        {
            for (hsql::Expr * expr : fields)
            {
                switch (expr->type)
                {
                    case hsql::kExprStar:
                        for (int i = 0; i < ans[0].getSize(); i++)printf("|  | ");

                        break;

                    case hsql::kExprColumnRef:

                        printf("|  | ");

                        break;

                    case hsql::kExprFunctionRef:
                    {
                        std::string f = expr->name;

                        if (f == "AVG")
                        {
                            printf("| %s(%s) = %.2lf | ", expr->name, expr->expr->name, double(sum[std::string(expr->expr->name)]) / num[std::string(expr->expr->name)]);
                        }
                        else if (f == "SUM")
                        {
                            printf("| %s(%s) = %lld | ", expr->name, expr->expr->name, sum[std::string(expr->expr->name)]);
                        }
                        else if (f == "MAX")
                        {
                            printf("| %s(%s) = %d | ", expr->name, expr->expr->name, ma[std::string(expr->expr->name)]);
                        }
                        else if (f == "MIN")
                        {
                            printf("| %s(%s) = %d | ", expr->name, expr->expr->name, mi[std::string(expr->expr->name)]);
                        }
                        else
                        {
                            fprintf(stderr, "Unsupport function %s\n", expr->name);
                        }
                    }
                    break;

                    default:
                        fprintf(stderr, "Expr type is error.\n");
                        return Error;
                }
            }

            printf("\n");
        }

        printf("\n");

        for (auto it : data)
        {
            it.second.clear();
        }
    }

    RC deleteRecord(hsql::Expr *wheres)
    {
        std::map<string, int> st = makeHeadMap();
        std::vector<RID> ans;
        bool flag = false;
        std::map<RID, RM_Record> set;
        std::vector<std::pair<RID, RM_Record> > data;

        if (wheres && getSet(*wheres, st, set, flag) == Error)return Error;

        if (flag)
        {
            for (auto it : set)
            {
                data.push_back(it);
                ans.push_back(it.first);
            }
        }
        else
        {
            data = rmfh->ListRec();

            for (auto it : data)
            {
                bool flag;

                if (wheres && check(*wheres, st, it.second, flag) == Error)
                {
                    return Error;
                }

                if (!wheres || flag)ans.push_back(it.first);
            }
        }

        for (RID rid : ans)
        {
            RM_Record record;
            rmfh->GetRec(rid, record);

            for (int i = 0; i < indexv.size(); i++)if (indexv[i])
                {
                    indexv[i]->DeleteEntry(record.get(i), rid);
                }

            record.clear();
            rmfh->DeleteRec(rid);
        }

        for (auto it : data)
        {
            it.second.clear();
        }
    }

    RC updateRecord(std::vector<hsql::UpdateClause *> &update, hsql::Expr *wheres)
    {
        std::map<string, int> st = makeHeadMap();

        for (auto it : update)
        {
            if (st.find(string(it->column)) == st.end())
            {
                fprintf(stderr, "Column %s is not found.\n", it->column);
                return Error;
            }
        }

        std::vector<RM_Record> rec;
        std::vector<RID> rid;
        bool flag = false;
        std::map<RID, RM_Record> set;
        std::vector<std::pair<RID, RM_Record> > data;

        if (wheres && getSet(*wheres, st, set, flag) == Error)return Error;

        if (flag)
        {
            for (auto it : set)
            {
                data.push_back(it);
                rid.push_back(it.first);
                rec.push_back(it.second);
            }
        }
        else
        {
            data = rmfh->ListRec();

            for (auto it : data)
            {
                bool flag;

                if (wheres && check(*wheres, st, it.second, flag) == Error)
                {
                    return Error;
                }

                if (!wheres || flag)rid.push_back(it.first), rec.push_back(it.second);
            }
        }

        std::vector<RM_Record> ans(rec.size());

        bf::path filename = path / configFile;
        std::ifstream fi(filename.string());
        int n, m;
        fi >> n;

        for (int i = 0; i < n; i++)
        {
            std::string name, type;
            bool notnull, index, primary;
            int len;
            getline(fi, name);

            if (name.empty())getline(fi, name);

            fi >> type >> len >> notnull >> index >> primary;
            bool f = false;
            hsql::Expr *expr;

            for (auto it : update)
            {
                if (name == std::string(it->column))
                {
                    f = true;
                    expr = it->value;
                }
            }

            if (!f)
            {
                for (int j = 0; j < rec.size(); j++)ans[j].push_back(rec[j].get(i));

                continue;
            }

            if (primary)
            {
                fprintf(stderr, "Primary Key can't update.\n");
                return Error;
            }

            Type *data;

            switch (expr->type)
            {
                case hsql::kExprLiteralInt:
                    if (type == "INTEGER" || type == "INT")
                    {
                        data = Type::make(false, expr->ival, len);
                    }
                    else
                    {
                        fprintf(stderr, "Update Column %s type is error.\n", name.c_str());
                        return Error;
                    }

                    break;

                case hsql::kExprLiteralString:
                    if (type == "CHAR" || type == "VARCHAR")
                    {
                        if (strlen(expr->name) > len)
                        {
                            fprintf(stderr, "Update Value '%s' is longer than %d.\n", expr->name, len);
                            return Error;
                        }

                        data = Type::make(false, expr->name, len);
                    }
                    else
                    {
                        fprintf(stderr, "Update type is error.\n");
                        return Error;
                    }

                    break;

                case hsql::kExprLiteralNull:
                    if (notnull)
                    {
                        fprintf(stderr, "Values[%d] can't be null.\n", i);
                        return Error;

                    }
                    else if (type == "INTEGER" || type == "INT")
                    {
                        data = Type::make(true, 0, len);
                    }
                    else if (type == "CHAR" || type == "VARCHAR")
                    {
                        data = Type::make(true, "", len);
                    }
                    else
                    {
                        fprintf(stderr, "Update Column %s type is error.\n", name.c_str());
                        return Error;
                    }


                    break;

                default:
                    fprintf(stderr, "Update type is error.\n");
                    return Error;
            }

            for (int j = 0; j < rec.size(); j++)ans[j].push_back(data);
        }

        fi >> m;
        vector<hsql::Expr *> checks;

        for (int i = 0; i < m; i++)
        {
            std::string expr;
            getline(fi, expr);

            if (expr.empty())getline(fi, expr);

            hsql::SQLParserResult *result = hsql::SQLParser::parseSQLString(expr);

            if (result->isValid)
            {
                for (hsql::SQLStatement * stmt : result->statements)
                {
                    if (stmt->type() == hsql::kStmtSelect)
                    {
                        checks.push_back(((hsql::SelectStatement *)stmt)->whereClause);
                    }
                    else
                    {
                        fprintf(stderr, "Check expr is error\n");
                        return Error;
                    }
                }
            }
            else
            {
                fprintf(stderr, "Check expr is error\n");
                return Error;
            }
        }



        for (hsql::Expr * expr : checks)
        {
            for (RM_Record rec : ans)
            {
                bool flag;

                if (expr && check(*expr, st, rec, flag) == Error)return Error;

                if (!flag)
                {
                    fprintf(stderr, "Check exprs equal false\n");
                    return Error;
                }
            }
        }

        for (RID rec : rid)
        {
            RM_Record record;
            rmfh->GetRec(rec, record);

            for (int i = 0; i < indexv.size(); i++)if (indexv[i])
                    indexv[i]->DeleteEntry(record.get(i), rec);

            record.clear();
            rmfh->DeleteRec(rec);
        }

        for (RM_Record rec : ans)
        {
            RID rid;
            rmfh->InsertRec(rec, rid);

            for (int i = 0; i < indexv.size(); i++)if (indexv[i])
                    indexv[i]->InsertEntry(rec.get(i), rid);
        }


        for (auto it : data)
        {
            it.second.clear();
        }
    }

};


#endif
