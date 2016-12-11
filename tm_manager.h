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
    RM_FileHandle *rmfh;
    bf::path path;
public:
    TM_Manager(FileManager *fm, BufPageManager *bpm, bf::path path)
        :path(path)
    {
        rmm = new RM_Manager(fm, bpm);
        rmfh = new RM_FileHandle(path);
        rmm->CreateFile((path/"data.db").string().c_str());
        rmm->OpenFile((path/"data.db").string().c_str(), rmfh);
    }

    ~TM_Manager()
    {
        rmm->CloseFile(rmfh);
        delete rmfh;
        delete rmm;
    }

    std::map<string, int> makeHeadMap()
    {
        bf::path filename = path/configFile;
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

    RC insertRecord(std::vector<hsql::Expr*> values)
    {

        bf::path filename = path/configFile;
        std::ifstream fi(filename.string());
        int n;
        fi >> n;
        if(n != int(values.size()))
        {
            printf("There are %d columns in this table but insert %d columns\n", n, int(values.size()));
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
            switch (values[i]->type) {
            case hsql::kExprLiteralInt:
                if (type == "INTEGER" || type == "INT")
                {
                    data = new Type_int(!notnull, values[i]->ival);
                }
                else
                {
                    printf("Values[%d] type is error.\n", i);
                    return Error;
                }
                break;
            case hsql::kExprLiteralString:
                if (type == "CHAR" || type == "VARCHAR")
                {
                    if(strlen(values[i]->name) > len)
                    {
                        printf("Values[%d] '%s' is longer than %d.\n", i, values[i]->name, len);
                        return Error;
                    }
                    if (len <= 32)data = new Type_varchar<32>(!notnull, values[i]->name, strlen(values[i]->name));
                    else if (len <= 64)data = new Type_varchar<64>(!notnull, values[i]->name, strlen(values[i]->name));
                    else if (len <= 128)data = new Type_varchar<128>(!notnull, values[i]->name, strlen(values[i]->name));
                    else if (len <= 256)data = new Type_varchar<256>(!notnull, values[i]->name, strlen(values[i]->name));
                }
                else
                {
                    printf("Values[%d] type is error.\n", i);
                    return Error;
                }
                break;
            default:
                printf("Values[%d] type is error.\n", i);
                return Error;
            }

            head.push_back(data);
        }

        RID rid;
        RC result = rmfh->InsertRec(head, rid);
        return result;

    }

    RC check(const hsql::Expr &expr, const std::map<string, int> &st, RM_Record &rec, bool &flag)
    {
        if(expr.type != hsql::kExprOperator)
        {
            printf("Where Expr should be a bool expression.\n");
            return Error;
        }

        int tleft = 0;
        int ileft;
        const char * cleft;
        bool bleft;
        switch(expr.expr->type)
        {
        case hsql::kExprColumnRef:
        {
            auto it = st.find(std::string(expr.expr->name));
            if(it == st.end())
            {
                printf("Column %s is not found.\n", expr.expr->name);
                return Error;
            }
            Type *t = rec.get(it->second);
            if(dynamic_cast<Type_int *>(t) != NULL)
            {
                tleft = 0;
                ileft = ((Type_int *)(t))->getValue();
            }
            else if (dynamic_cast<Type_varchar<32>*>(t) != NULL)
            {
                tleft = 1;
                cleft = ((Type_varchar<32>*)(t))->getStr();
            }
            else if (dynamic_cast<Type_varchar<64>*>(t) != NULL)
            {
                tleft = 1;
                cleft = ((Type_varchar<64>*)(t))->getStr();
            }
            else if (dynamic_cast<Type_varchar<128>*>(t) != NULL)
            {
                tleft = 1;
                cleft = ((Type_varchar<128>*)(t))->getStr();
            }
            else if (dynamic_cast<Type_varchar<256>*>(t) != NULL)
            {
                tleft = 1;
                cleft = ((Type_varchar<256>*)(t))->getStr();
            }
            else
            {
                printf("The Expr Column Type is error.\n");
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
        default:
            printf("The Expr Literal Type is error.\n");
            return Error;
        }

        if(expr.op_type == hsql::Expr::NOT)
        {
            if(tleft == 2)
            {
                flag = !bleft;
                return Success;
            }
            else
            {
                printf("The Expr Type is error.\n");
                return Error;
            }
        }

        int tright = 0;
        int iright;
        const char * cright;
        bool bright;
        switch(expr.expr2->type)
        {
        case hsql::kExprColumnRef:
        {
            auto it = st.find(std::string(expr.expr2->name));
            if(it == st.end())
            {
                printf("Column %s is not found.\n", expr.expr2->name);
                return Error;
            }
            Type *t = rec.get(it->second);
            if(dynamic_cast<Type_int *>(t) != NULL)
            {
                tright = 0;
                iright = ((Type_int *)(t))->getValue();
            }
            else if (dynamic_cast<Type_varchar<32>*>(t) != NULL)
            {
                tright = 1;
                cright = ((Type_varchar<32>*)(t))->getStr();
            }
            else if (dynamic_cast<Type_varchar<64>*>(t) != NULL)
            {
                tright = 1;
                cright = ((Type_varchar<64>*)(t))->getStr();
            }
            else if (dynamic_cast<Type_varchar<128>*>(t) != NULL)
            {
                tright = 1;
                cright = ((Type_varchar<128>*)(t))->getStr();
            }
            else if (dynamic_cast<Type_varchar<256>*>(t) != NULL)
            {
                tright = 1;
                cright = ((Type_varchar<256>*)(t))->getStr();
            }
            else
            {
                printf("The Expr Column Type is error.\n");
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
        default:
            printf("The Expr Literal Type is error.\n");
            return Error;
        }

        if(tleft != tright)
        {
            printf("The Expr Type is error.\n");
            return Error;
        }

        switch (expr.op_type) {
        case hsql::Expr::SIMPLE_OP:

            if(expr.op_char == '=')
            {
                if(tleft == 0)
                    flag = (ileft == iright);
                else if(tleft == 1)
                    flag = (strcmp(cleft, cright) == 0);
                else
                {
                    printf("The Expr Type is error.\n");
                    return Error;
                }
            }
            else if(expr.op_char == '<')
            {
                if(tleft == 0)
                    flag = (ileft < iright);
                else if(tleft == 1)
                    flag = (strcmp(cleft, cright) < 0);
                else
                {
                    printf("The Expr Type is error.\n");
                    return Error;
                }
            }
            else if(expr.op_char == '>')
            {
                if(tleft == 0)
                    flag = (ileft > iright);
                else if(tleft == 1)
                    flag = (strcmp(cleft, cright) > 0);
                else
                {
                    printf("The Expr Type is error.\n");
                    return Error;
                }
            }
            break;
        case hsql::Expr::NOT_EQUALS:
            if(tleft == 0)
                flag = (ileft != iright);
            else if(tleft == 1)
                flag = (strcmp(cleft, cright) != 0);
            else
            {
                printf("The Expr Type is error.\n");
                return Error;
            }
            break;
        case hsql::Expr::LESS_EQ:
            if(tleft == 0)
                flag = (ileft <= iright);
            else if(tleft == 1)
                flag = (strcmp(cleft, cright) <= 0);
            else
            {if(tleft == 0)
                    flag = (ileft != iright);
                else if(tleft == 1)
                    flag = (strcmp(cleft, cright) != 0);
                else
                {
                    printf("The Expr Type is error.\n");
                    return Error;
                }
                printf("The Expr Type is error.\n");
                return Error;
            }
            break;
        case hsql::Expr::GREATER_EQ:
            if(tleft == 0)
                flag = (ileft >= iright);
            else if(tleft == 1)
                flag = (strcmp(cleft, cright) >= 0);
            else
            {
                printf("The Expr Type is error.\n");
                return Error;
            }
            break;
        case hsql::Expr::AND:
            if(tleft == 2)
                flag = (bleft && bright);
            else
            {
                printf("The Expr Type is error.\n");
                return Error;
            }
            break;
        case hsql::Expr::OR:
            if(tleft == 2)
                flag = (bleft || bright);
            else
            {
                printf("The Expr Type is error.\n");
                return Error;
            }
            break;
//        case hsql::Expr::NOT:
//            break;
        default:
            printf("The Expr Operation is error.\n");
            return Error;
            break;
        }
        return Success;

    }

    RC selectRecord(std::vector<hsql::Expr*> &fields, hsql::Expr *wheres)
    {
        std::vector<std::pair<RID, RM_Record> > data = rmfh->ListRec();
        std::map<string, int> st = makeHeadMap();
        std::vector<RM_Record> ans;
        for(auto it : data)
        {
            bool flag;
            if(wheres && check(*wheres, st, it.second, flag) == Error)
            {
                return Error;
            }
            if(!wheres || flag)ans.push_back(it.second);
        }
        for(RM_Record rec : ans)
        {
            for(hsql::Expr* expr : fields)
            {
                switch(expr->type)
                {
                case hsql::kExprStar:
                    rec.print();
                    break;
                case hsql::kExprColumnRef:
                {
                    auto it = st.find(std::string(expr->name));
                    if(it == st.end())
                    {
                        printf("Column %s is not found.\n", expr->name);
                        return Error;
                    }
                    Type *t = rec.get(it->second);
                    t->print();
                }
                    break;
                default:
                    printf("Expr type is error.\n");
                    return Error;
                }
            }
            printf("\n");
        }
        printf("\n");
        for(auto it : data)
        {
            it.second.clear();
        }
    }

    RC deleteRecord(hsql::Expr *wheres)
    {
        std::vector<std::pair<RID, RM_Record> > data = rmfh->ListRec();
        std::map<string, int> st = makeHeadMap();
        std::vector<RID> ans;
        for(auto it : data)
        {
            bool flag;
            if(wheres && check(*wheres, st, it.second, flag) == Error)
            {
                return Error;
            }
            if(!wheres || flag)ans.push_back(it.first);
        }
        for(RID rec : ans)
        {
            rmfh->DeleteRec(rec);
        }
        for(auto it : data)
        {
            it.second.clear();
        }
    }

    RC updateRecord(std::vector<hsql::UpdateClause*> &update, hsql::Expr *wheres)
    {
        std::map<string, int> st = makeHeadMap();
        for(auto it : update)
        {
            if(st.find(string(it->column)) == st.end())
            {
                printf("Column %s is not found.\n", it->column);
                return Error;
            }
        }
        std::vector<std::pair<RID, RM_Record> > data = rmfh->ListRec();

        std::vector<RID> rid;
        std::vector<RM_Record> rec;
        for(auto it : data)
        {
            bool flag;
            if(wheres && check(*wheres, st, it.second, flag) == Error)
            {
                return Error;
            }
            if(!wheres || flag)rid.push_back(it.first), rec.push_back(it.second);
        }
        for(RID rec : rid)
        {
            rmfh->DeleteRec(rec);
        }

        std::vector<RM_Record> ans(rec.size());

        bf::path filename = path/configFile;
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
            bool f = false;
            hsql::Expr *expr;
            for(auto it : update)
            {
                if(name == std::string(it->column))
                {
                    f = true;
                    expr = it->value;
                }
            }
            if(!f)
            {
                for(int j=0;j<rec.size();j++)ans[j].push_back(rec[j].get(i));
                continue;
            }
            Type *data;
            switch (expr->type) {
            case hsql::kExprLiteralInt:
                if (type == "INTEGER" || type == "INT")
                {
                    data = new Type_int(!notnull, expr->ival);
                }
                else
                {
                    printf("Update Column %s type is error.\n", name.c_str());
                    return Error;
                }
                break;
            case hsql::kExprLiteralString:
                if (type == "CHAR" || type == "VARCHAR")
                {
                    if(strlen(expr->name) > len)
                    {
                        printf("Update Value '%s' is longer than %d.\n", expr->name, len);
                        return Error;
                    }
                    if (len <= 32)data = new Type_varchar<32>(!notnull, expr->name, strlen(expr->name));
                    else if (len <= 64)data = new Type_varchar<64>(!notnull, expr->name, strlen(expr->name));
                    else if (len <= 128)data = new Type_varchar<128>(!notnull, expr->name, strlen(expr->name));
                    else if (len <= 256)data = new Type_varchar<256>(!notnull, expr->name, strlen(expr->name));
                }
                else
                {
                    printf("Update type is error.\n");
                    return Error;
                }
                break;
            default:
                printf("Update type is error.\n");
                return Error;
            }

            for(int j=0;j<rec.size();j++)ans[j].push_back(data);
        }

        for(RM_Record rec : ans)
        {
            RID rid;
            rmfh->InsertRec(rec, rid);
        }


        for(auto it : data)
        {
            it.second.clear();
        }
    }

};


#endif
