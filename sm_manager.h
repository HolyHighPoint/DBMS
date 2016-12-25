#ifndef SM_MANAGER_H
#define SM_MANAGER_H
#include "rc.h"
#include <boost/filesystem.hpp>
#include <fstream>
#include <bufmanager/BufPageManager.h>
#include <fileio/FileManager.h>
#include <map>
#include <set>
#include "sql/statements.h"
#include "sql/Expr.h"
#include "rm_record.h"
#include "tm_manager.h"


namespace bf = boost::filesystem;

class SM_Manager
{
private:
    SM_Manager()
    {
        MyBitMap::initConst();
        fm = new FileManager();
        bpm = new BufPageManager(fm);
    }

    ~SM_Manager()
    {
        for (auto it : tbsta)
        {
            delete it.second;
        }

        delete fm;
        delete bpm;
    }

    static SM_Manager *m_instance;
    class CGarbo
    {
    public:
        ~CGarbo()
        {
            if (SM_Manager::m_instance)
                delete SM_Manager::m_instance;
        }
    };
    static CGarbo Garbo;
    std::string curdb;
    FileManager *fm;
    BufPageManager *bpm;
    std::map<bf::path, TM_Manager *> tbsta;
public:
    static SM_Manager *getInstance()
    {
        if (m_instance == NULL)
            m_instance = new SM_Manager();

        return m_instance;
    }

    RC createDatabase(const char *name)
    {
        std::ifstream fi(configFile, std::fstream::in);
        std::string buf;

        while (getline(fi, buf))
        {
            if (strcmp(buf.c_str(), name) == 0)
            {
                fprintf(stderr, "Database %s already exists\n", name);
                return Error;
            }
        }

        fi.close();
        bf::path workPath = bf::current_path();
        bf::path path = workPath / name;

        if (bf::exists(path))
        {
            fprintf(stderr, "Database directory %s already exists\n", path.c_str());
            return Error;
        }

        bf::create_directory(path);
        std::ofstream fo(configFile, std::fstream::app);
        fo << std::string(name) << std::endl;
        fo.close();
        return Success;
    }

    RC dropDatabase(const char *name)
    {
        std::ifstream fi(configFile, std::fstream::in);
        std::string buf;
        std::vector<std::string> dbs;
        bool f = false;

        while (getline(fi, buf))
        {
            if (strcmp(buf.c_str(), name) == 0)f = true;
            else dbs.push_back(buf);
        }

        fi.close();

        if (!f)
        {
            fprintf(stderr, "Database %s doesn't' exist\n", name);
            return Error;
        }

        if (strcmp(curdb.c_str(), name) == 0)curdb.clear();

        bf::path workPath = bf::current_path();
        bf::path path = workPath / name;

        if (bf::exists(path))
            bf::remove_all(path);

        std::ofstream fo(configFile);

        for (std::string s : dbs)fo << s << std::endl;

        fo.close();
        return Success;
    }

    RC useDatabase(const char *name)
    {
        std::ifstream fi(configFile, std::fstream::in);
        std::string buf;
        bool f = false;

        while (getline(fi, buf))
        {
            if (strcmp(buf.c_str(), name) == 0)
            {
                bf::path workPath = bf::current_path();
                bf::path path = workPath / name;

                if (bf::exists(path) && bf::is_directory(path))
                {
                    curdb = std::string(name);
                    f = true;
                }
            }
        }

        fi.close();

        if (!f)
        {
            fprintf(stderr, "Database %s doesn't exist\n", name);
            return Error;
        }

        return Success;
    }

    RC showDatabases()
    {
        std::ifstream fi(configFile, std::fstream::in);
        std::string buf;
        bool f = false;

        while (getline(fi, buf))
        {
            printf("%s\n", buf.c_str());
        }

        printf("\n");
        fi.close();
        return Success;
    }

    RC showTables()
    {
        if (curdb.empty())
        {
            fprintf(stderr, "There is no current database\n");
            return Error;
        }

        bf::path workPath = bf::current_path() / curdb;
        std::ifstream fi((workPath / configFile).string(), std::fstream::in);
        std::string buf;

        while (getline(fi, buf))
        {
            printf("%s\n", buf.c_str());
        }

        printf("\n");

        fi.close();
    }

    RC dropTable(const char *name)
    {
        if (curdb.empty())
        {
            fprintf(stderr, "There is no current database\n");
            return Error;
        }

        bf::path workPath = bf::current_path() / curdb;
        std::ifstream fi((workPath / configFile).string(), std::fstream::in);
        std::string buf;
        std::vector<std::string> tbs;
        bool f = false;

        while (getline(fi, buf))
        {
            if (strcmp(buf.c_str(), name) == 0)f = true;
            else tbs.push_back(buf);
        }

        fi.close();

        if (!f)
        {
            fprintf(stderr, "Table %s doesn't' exist\n", name);
            return Error;
        }

        bf::path path = workPath / name;

        if (bf::exists(path))
            bf::remove_all(path);

        std::ofstream fo((workPath / configFile).string());

        for (std::string s : tbs)fo << s << std::endl;

        fo.close();
        return Success;
    }


    RC createTable(const char *name, std::vector<hsql::ColumnDefinition *> &columns)
    {
        if (curdb.empty())
        {
            fprintf(stderr, "There is no current database\n");
            return Error;
        }

        bf::path workPath = bf::current_path() / curdb;
        std::ifstream fi((workPath / configFile).string(), std::fstream::in);
        std::string buf;

        while (getline(fi, buf))
        {
            if (strcmp(buf.c_str(), name) == 0)
            {
                fprintf(stderr, "Table %s already exists\n", name);
                return Error;
            }
        }

        fi.close();

        bf::path path = workPath / name;

        if (bf::exists(path))
        {
            fprintf(stderr, "Table directory %s already exists\n", path.c_str());
            return Error;
        }

        bf::create_directory(path);
        std::ofstream fo((workPath / configFile).string(), std::fstream::app);
        fo << std::string(name) << std::endl;
        fo.close();
        fo.open((path / configFile).string());

        std::string primary;

        std::vector<hsql::ColumnDefinition *> checks;

        for (int i = 0; i < columns.size(); i++)
            if (columns[i]->type == hsql::ColumnDefinition::PRIMARY)
            {
                if (!primary.empty())
                {
                    fprintf(stderr, "Table %s already has primary key %s\n", name, primary.c_str());
                    fo.close();
                    bf::remove(path / configFile);
                    return Error;
                }

                primary = std::string(columns[i]->name);
                columns.erase(columns.begin() + (i--));
            }
            else if (columns[i]->type == hsql::ColumnDefinition::CHECK)
            {
                checks.push_back(columns[i]);
                columns.erase(columns.begin() + (i--));
            }

        for (int i = 0; i < columns.size() - 1; i++)
            for (int j = i + 1; j < columns.size(); j++)
                if (strcmp(columns[i]->name, columns[j]->name) == 0)
                {
                    fprintf(stderr, "Table %s already has key %s\n", name, primary.c_str());
                    fo.close();
                    bf::remove(path / configFile);
                    return Error;
                }


        fo << columns.size() << std::endl;

        int checknum;

        for (hsql::ColumnDefinition * it : columns)
        {
            fo << it->name << std::endl;

            switch (it->type)
            {
                case hsql::ColumnDefinition::INTEGER:
                    fo << "INTEGER" << -1 << " ";
                    break;

                case hsql::ColumnDefinition::TINYINT:
                    fo << "INTEGER" << -1 << " ";
                    break;

                case hsql::ColumnDefinition::INT:
                    fo << "INT" << " " << it->len << " ";
                    break;

                case hsql::ColumnDefinition::CHAR:
                    fo << "CHAR" << " " << it->len << " ";
                    break;

                case hsql::ColumnDefinition::VARCHAR:
                    fo << "VARCHAR" << " " << it->len << " ";
                    break;

            }

            fo << it->notnull << " " << (std::string(it->name) == primary) << " " << (std::string(it->name) == primary) << std::endl;

        }

        fo << checks.size() << std::endl;

        for (hsql::ColumnDefinition * it : checks)
        {
            fo << "SELECT * FROM " << name << " WHERE " << it->expr->toString() << std::endl;
        }

        return Success;
    }

    RC descTable(const char *name)
    {
        if (curdb.empty())
        {
            fprintf(stderr, "There is no current database\n");
            return Error;
        }

        bf::path workPath = bf::current_path() / curdb;
        std::ifstream fi((workPath / configFile).string(), std::fstream::in);
        std::string buf;
        bool f;

        while (getline(fi, buf))
        {
            if (strcmp(buf.c_str(), name) == 0)
            {
                bf::path path = workPath / name;

                if (bf::exists(path) && bf::is_directory(path))
                    f = true;
            }
        }

        fi.close();

        if (!f)
        {
            fprintf(stderr, "Table %s doesn't exist\n", name);
            return Error;
        }

        bf::path path = workPath / name;
        fi.open((path / configFile).string());
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
            printf("%s: %s", name.c_str(), type.c_str());

            if (len != -1)printf("(%d) ", len);

            printf("--%s, %s, %s\n", notnull ? "Not NULL" : "NULL", index ? "Indexed" : "Unindexed", primary ? "Primary" : "Not Primary");
        }

        printf("\n");

        return Success;
    }

    RC insertRecord(const char *name, std::vector<hsql::Expr *> &values)
    {
        if (curdb.empty())
        {
            fprintf(stderr, "There is no current database\n");
            return Error;
        }

        bf::path workPath = bf::current_path() / curdb;
        std::ifstream fi((workPath / configFile).string(), std::fstream::in);
        std::string buf;
        bool f;

        while (getline(fi, buf))
        {
            if (strcmp(buf.c_str(), name) == 0)
            {
                bf::path path = workPath / name;

                if (bf::exists(path) && bf::is_directory(path))
                    f = true;
            }
        }

        fi.close();

        if (!f)
        {
            fprintf(stderr, "Table %s doesn't exist\n", name);
            return Error;
        }

        bf::path path = workPath / name;

        auto it = tbsta.find(path);

        if (it == tbsta.end())
        {
            tbsta.insert(make_pair(path, new TM_Manager(fm, bpm, path)));
            it = tbsta.find(path);
        }

        return it->second->insertRecord(values);
    }

    RC selectRecord(const char *name, std::vector<hsql::Expr *> &fields, hsql::Expr *wheres, hsql::OrderDescription *order, hsql::LimitDescription *limit, hsql::GroupByDescription *group)
    {
        if (curdb.empty())
        {
            fprintf(stderr, "There is no current database\n");
            return Error;
        }

        bf::path workPath = bf::current_path() / curdb;
        std::ifstream fi((workPath / configFile).string(), std::fstream::in);
        std::string buf;
        bool f;

        while (getline(fi, buf))
        {
            if (strcmp(buf.c_str(), name) == 0)
            {
                bf::path path = workPath / name;

                if (bf::exists(path) && bf::is_directory(path))
                    f = true;
            }
        }

        fi.close();

        if (!f)
        {
            fprintf(stderr, "Table %s doesn't exist\n", name);
            return Error;
        }

        bf::path path = workPath / name;

        auto it = tbsta.find(path);

        if (it == tbsta.end())
        {
            tbsta.insert(make_pair(path, new TM_Manager(fm, bpm, path)));
            it = tbsta.find(path);
        }

        return it->second->selectRecord(fields, wheres, order, limit, group);

    }

    RC deleteRecord(const char *name, hsql::Expr *wheres)
    {
        if (curdb.empty())
        {
            fprintf(stderr, "There is no current database\n");
            return Error;
        }

        bf::path workPath = bf::current_path() / curdb;
        std::ifstream fi((workPath / configFile).string(), std::fstream::in);
        std::string buf;
        bool f;

        while (getline(fi, buf))
        {
            if (strcmp(buf.c_str(), name) == 0)
            {
                bf::path path = workPath / name;

                if (bf::exists(path) && bf::is_directory(path))
                    f = true;
            }
        }

        fi.close();

        if (!f)
        {
            fprintf(stderr, "Table %s doesn't exist\n", name);
            return Error;
        }

        bf::path path = workPath / name;

        auto it = tbsta.find(path);

        if (it == tbsta.end())
        {
            tbsta.insert(make_pair(path, new TM_Manager(fm, bpm, path)));
            it = tbsta.find(path);
        }

        return it->second->deleteRecord(wheres);

    }

    RC updateRecord(const char *name, std::vector<hsql::UpdateClause *> &updates, hsql::Expr *wheres)
    {
        if (curdb.empty())
        {
            fprintf(stderr, "There is no current database\n");
            return Error;
        }

        bf::path workPath = bf::current_path() / curdb;
        std::ifstream fi((workPath / configFile).string(), std::fstream::in);
        std::string buf;
        bool f;

        while (getline(fi, buf))
        {
            if (strcmp(buf.c_str(), name) == 0)
            {
                bf::path path = workPath / name;

                if (bf::exists(path) && bf::is_directory(path))
                    f = true;
            }
        }

        fi.close();

        if (!f)
        {
            fprintf(stderr, "Table %s doesn't exist\n", name);
            return Error;
        }

        bf::path path = workPath / name;

        auto it = tbsta.find(path);

        if (it == tbsta.end())
        {
            tbsta.insert(make_pair(path, new TM_Manager(fm, bpm, path)));
            it = tbsta.find(path);
        }

        return it->second->updateRecord(updates, wheres);

    }

    RC createIndex(const char *name, const char *indexname)
    {
        if (curdb.empty())
        {
            fprintf(stderr, "There is no current database\n");
            return Error;
        }

        bf::path workPath = bf::current_path() / curdb;
        std::ifstream fi((workPath / configFile).string());
        std::string buf;
        bool f;

        while (getline(fi, buf))
        {
            if (strcmp(buf.c_str(), name) == 0)
            {
                bf::path path = workPath / name;

                if (bf::exists(path) && bf::is_directory(path))
                    f = true;
            }
        }

        fi.close();

        if (!f)
        {
            fprintf(stderr, "Table %s doesn't exist\n", name);
            return Error;
        }

        bf::path path = workPath / name;
        fi.open((path / configFile).string());
        char str[1024];
        int n;
        fi >> n;
        sprintf(str, "%d\n", n);
        bool flag = false;

        for (int i = 0; i < n; i++)
        {
            std::string name, type;
            bool notnull, index, primary;
            int len;
            getline(fi, name);

            if (name.empty())getline(fi, name);

            sprintf(str + strlen(str), "%s\n", name.c_str());
            fi >> type >> len >> notnull >> index >> primary;

            if (string(indexname) == name)
            {
                if (index)
                {
                    fprintf(stderr, "Column %s Index already exists\n", indexname);
                    return Error;
                }

                index = true;
                flag = true;
            }

            sprintf(str + strlen(str), "%s %d %d %d %d\n", type.c_str(), len, notnull, index, primary);
        }

        fi >> n;
        sprintf(str + strlen(str), "%d\n", n);

        for (int i = 0; i < n; i++)
        {
            std::string check;
            getline(fi, check);

            if (check.empty())getline(fi, check);

            sprintf(str + strlen(str), "%s\n", check.c_str());
        }

        fi.close();

        if (!flag)
        {
            fprintf(stderr, "Column %s doesn't exist\n", indexname);
            return Error;
        }

        std::ofstream fo((path / configFile).string());
        fo << str;
        fo.close();
        auto it = tbsta.find(path);

        if (it == tbsta.end())
        {
            tbsta.insert(make_pair(path, new TM_Manager(fm, bpm, path)));
            it = tbsta.find(path);
        }

        return it->second->createIndex(true);

    }

    RC dropIndex(const char *name, const char *indexname)
    {
        if (curdb.empty())
        {
            fprintf(stderr, "There is no current database\n");
            return Error;
        }

        bf::path workPath = bf::current_path() / curdb;
        std::ifstream fi((workPath / configFile).string());
        std::string buf;
        bool f;

        while (getline(fi, buf))
        {
            if (strcmp(buf.c_str(), name) == 0)
            {
                bf::path path = workPath / name;

                if (bf::exists(path) && bf::is_directory(path))
                    f = true;
            }
        }

        fi.close();

        if (!f)
        {
            fprintf(stderr, "Table %s doesn't exist\n", name);
            return Error;
        }

        bf::path path = workPath / name;
        fi.open((path / configFile).string());
        char str[1024];
        int n;
        fi >> n;
        sprintf(str, "%d\n", n);
        bool flag = false;

        for (int i = 0; i < n; i++)
        {
            std::string name, type;
            bool notnull, index, primary;
            int len;
            getline(fi, name);

            if (name.empty())getline(fi, name);

            sprintf(str + strlen(str), "%s\n", name.c_str());
            fi >> type >> len >> notnull >> index >> primary;

            if (string(indexname) == name)
            {
                if (!index)
                {
                    fprintf(stderr, "Column %s Index doesn't exist\n", indexname);
                    return Error;
                }

                if (primary)
                {
                    fprintf(stderr, "Column %s is Primary Key\n", indexname);
                    return Error;
                }

                index = false;
                flag = true;
            }

            sprintf(str + strlen(str), "%s %d %d %d %d\n", type.c_str(), len, notnull, index, primary);
        }

        fi >> n;
        sprintf(str + strlen(str), "%d\n", n);

        for (int i = 0; i < n; i++)
        {
            std::string check;
            getline(fi, check);

            if (check.empty())getline(fi, check);

            sprintf(str + strlen(str), "%s\n", check.c_str());
        }

        fi.close();

        if (!flag)
        {
            fprintf(stderr, "Column %s doesn't exist\n", indexname);
            return Error;
        }

        std::ofstream fo((path / configFile).string());
        fo << str;
        fo.close();
        auto it = tbsta.find(path);

        if (it == tbsta.end())
        {
            tbsta.insert(make_pair(path, new TM_Manager(fm, bpm, path)));
            it = tbsta.find(path);
        }

        return it->second->dropIndex();

    }

    RC getSet(const hsql::Expr &expr, const std::map<std::string, TM_Manager *> nameSt, const std::map<std::string, std::map<string, int> > &headSt, std::set<std::map<std::string, RID> > &ans)
    {
        if (expr.type != hsql::kExprOperator)
        {
            fprintf(stderr, "Where Expr should be a bool expression.\n");
            return Error;
        }

        int tleft = 0;
        std::set<std::map<std::string, RID> > sleft;
        Type *data;
        IX_Manager *index;
        int lit;

        switch (expr.expr->type)
        {
            case hsql::kExprColumnRef:
            {
                auto itt = headSt.find(expr.expr->table);

                if (itt == headSt.end())
                {
                    fprintf(stderr, "Table %s is not found.\n", expr.expr->table);
                    return Error;
                }

                RM_Record head = nameSt.find(expr.expr->table)->second->rmfh->makeHead();
                const std::map<string, int> &st = itt->second;
                auto it = st.find(std::string(expr.expr->name));

                if (it == st.end())
                {
                    fprintf(stderr, "Column %s is not found.\n", expr.expr->name);
                    return Error;
                }

                data = head.get(it->second);

                if ((index = nameSt.find(expr.expr->table)->second->indexv[it->second]) == NULL)
                {
                    fprintf(stderr, "Column %s doesn't have index and creating index...\n", expr.expr->name);
                    createIndex(expr.expr->table, expr.expr->name);
                    index = nameSt.find(expr.expr->table)->second->indexv[it->second];
                }

                lit = it->second;
            }
            break;

            case hsql::kExprOperator:
            {
                tleft = 1;
                RC result = getSet(*expr.expr, nameSt, headSt, sleft);

                if (result == Error)
                {
                    return Error;
                }
            }
            break;

            default:
                fprintf(stderr, "Unsupported Select Expr.\n");
                return Error;
        }

        if (expr.op_type == hsql::Expr::NOT)
        {
            fprintf(stderr, "Unsupported Select Expr --- Not OP.\n");
            return Error;
        }

        int tright;
        std::set<std::map<std::string, RID> > sright;
        int iright;
        const char *cright;
        std::vector<std::pair<RID, int> > ilist;
        std::vector<std::pair<RID, std::string> > clist;

        switch (expr.expr2->type)
        {
            case hsql::kExprOperator:
            {
                tright = 1;
                RC result = getSet(*expr.expr2, nameSt, headSt, sright);

                if (result == Error)
                {
                    return Error;
                }
            }
            break;

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

            case hsql::kExprColumnRef:
            {
                auto itt = headSt.find(expr.expr2->table);

                if (itt == headSt.end())
                {
                    fprintf(stderr, "Table %s is not found.\n", expr.expr2->table);
                    return Error;
                }

                const std::map<string, int> &st = itt->second;
                auto it = st.find(std::string(expr.expr2->name));

                if (it == st.end())
                {
                    fprintf(stderr, "Column %s is not found.\n", expr.expr2->name);
                    return Error;
                }

                std::vector<std::pair<RID, RM_Record> > data = nameSt.find(expr.expr2->table)->second->rmfh->ListRec();

                for (std::pair<RID, RM_Record> p : data)
                {
                    if (p.second.get(it->second)->isInt())
                    {
                        ilist.push_back(make_pair(p.first, p.second.get(it->second)->getValue()));
                        tright = 5;
                    }
                    else if (p.second.get(it->second)->isStr())
                    {
                        clist.push_back(make_pair(p.first, p.second.get(it->second)->getStr()));
                        tright = 6;
                    }
                    else
                    {
                        fprintf(stderr, "Column %s.%s is not found.\n", expr.expr2->table, expr.expr2->name);
                        return Error;
                    }

                    p.second.clear();
                }

            }
            break;

            default:
                fprintf(stderr, "Unsupported Select Expr.\n");
                return Success;
        }



        if (tleft == tright && tleft == 1)
        {
            switch (expr.op_type)
            {
                case hsql::Expr::AND:
                {
                    typedef std::multimap<std::pair<std::string, RID>, std::map<std::string, RID> > multitype;
                    std::multimap<std::pair<std::string, RID>, std::map<std::string, RID> > multist;
                    std::set<std::string> lname, rname, name;

                    for (auto lit : sleft)
                    {
                        for (auto litit : lit)
                            lname.insert(litit.first);
                    }

                    for (auto rit : sright)
                    {
                        for (auto ritit : rit)
                            rname.insert(ritit.first);
                    }

                    for (auto lit : lname)
                        if (rname.find(lit)  != rname.end())
                            name.insert(lit);

                    for (auto lit : sleft)
                    {
                        for (auto it : name)
                        {
                            if (lit.find(it) != lit.end())
                                multist.insert(make_pair(*lit.find(it), lit));
                            else
                                multist.insert(make_pair(make_pair(it, RID()), lit));
                        }
                    }

                    for (auto rit : sright)
                    {
                        bool f;
                        std::set<std::map<std::string, RID> >tmp;

                        for (auto ritit : rit)
                        {
                            if (name.find(ritit.first) != name.end())
                            {
                                f = true;
                                auto ret = multist.equal_range(ritit);

                                for (auto it = ret.first; it != ret.second; it++)
                                    tmp.insert(it->second);

                                ret = multist.equal_range(make_pair(ritit.first, RID()));

                                for (auto it = ret.first; it != ret.second; it++)
                                    tmp.insert(it->second);

                                break;
                            }
                        }

                        if (!f)
                        {
                            for (auto lit : sleft)
                            {
                                std::map<std::string, RID> tmp = rit;
                                tmp.insert(lit.begin(), lit.end());
                                ans.insert(tmp);
                            }
                        }
                        else
                        {
                            for (auto lit : tmp)
                            {
                                bool ff = true;

                                if (f)
                                {
                                    for (auto litit : lit)
                                        for (auto ritit : rit)
                                            if (litit.first == ritit.first && litit.second != ritit.second)
                                            {
                                                ff = false;
                                                break;
                                            }
                                }

                                if (ff)
                                {
                                    std::map<std::string, RID> tmp = lit;
                                    tmp.insert(rit.begin(), rit.end());
                                    ans.insert(tmp);
                                }
                            }
                        }
                    }
                }

                break;

                case hsql::Expr::OR:
                    ans.insert(sleft.begin(), sleft.end());
                    ans.insert(sright.begin(), sright.end());

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
                            std::map<std::string, RID>st;
                            st.insert(make_pair(expr.expr->table, rid));
                            ans.insert(st);
                        }
                    }

                    else if (expr.op_char == '<')
                    {
                        Type *t = new Type_int(false, 0x80000000);
                        std::vector<RID> vec = index->SearchRangeEntry(t, data);

                        for (auto rid : vec)
                        {
                            RM_Record rec;
                            nameSt.find(expr.expr->table)->second->rmfh->GetRec(rid, rec);

                            if (*((Type_int *)rec.get(lit)) == *(Type_int *)data)
                            {
                                rec.clear();
                                continue;
                            }

                            rec.clear();

                            std::map<std::string, RID>st;
                            st.insert(make_pair(expr.expr->table, rid));
                            ans.insert(st);
                        }
                    }
                    else if (expr.op_char == '>')
                    {
                        Type *t = new Type_int(false, 0x7fffffff);
                        std::vector<RID> vec = index->SearchRangeEntry(data, t);

                        for (auto rid : vec)
                        {
                            RM_Record rec;
                            nameSt.find(expr.expr->table)->second->rmfh->GetRec(rid, rec);

                            if (*((Type_int *)rec.get(lit)) == *(Type_int *)data)
                            {
                                rec.clear();
                                continue;
                            }

                            rec.clear();
                            std::map<std::string, RID>st;
                            st.insert(make_pair(expr.expr->table, rid));
                            ans.insert(st);
                        }
                    }

                    break;

                case hsql::Expr::LESS_EQ:
                {
                    Type *t = new Type_int(false, 0x80000000);
                    std::vector<RID> vec = index->SearchRangeEntry(t, data);

                    for (auto rid : vec)
                    {
                        std::map<std::string, RID>st;
                        st.insert(make_pair(expr.expr->table, rid));
                        ans.insert(st);
                    }
                }
                break;

                case hsql::Expr::GREATER_EQ:
                {
                    Type *t = new Type_int(false, 0x7fffffff);
                    std::vector<RID> vec = index->SearchRangeEntry(data, t);

                    for (auto rid : vec)
                    {
                        std::map<std::string, RID>st;
                        st.insert(make_pair(expr.expr->table, rid));
                        ans.insert(st);
                    }
                }
                break;

                default:
                    fprintf(stderr, "Unsupported Select Expr.\n");
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
                            std::map<std::string, RID>st;
                            st.insert(make_pair(expr.expr->table, rid));
                            ans.insert(st);
                        }
                    }

                    break;

                default:
                    fprintf(stderr, "Unsupported Select Expr.\n");
                    return Error;
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
                            std::map<std::string, RID>st;
                            st.insert(make_pair(expr.expr->table, rid));
                            ans.insert(st);
                        }
                    }

                    break;

                default:
                    fprintf(stderr, "Unsupported Select Expr.\n");
                    return Error;
            }
        }
        else if (tleft == 0 && tright == 5)
        {
            for (auto p : ilist)
            {
                if (!data->set(p.second))
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
                                std::map<std::string, RID>st;
                                st.insert(make_pair(expr.expr->table, rid));
                                st.insert(make_pair(expr.expr2->table, p.first));
                                ans.insert(st);
                            }
                        }

                        else if (expr.op_char == '<')
                        {
                            Type *t = new Type_int(false, 0x80000000);
                            std::vector<RID> vec = index->SearchRangeEntry(t, data);

                            for (auto rid : vec)
                            {
                                RM_Record rec;
                                nameSt.find(expr.expr->table)->second->rmfh->GetRec(rid, rec);

                                if (*((Type_int *)rec.get(lit)) == *(Type_int *)data)
                                {
                                    rec.clear();
                                    continue;
                                }

                                rec.clear();

                                std::map<std::string, RID>st;
                                st.insert(make_pair(expr.expr->table, rid));
                                st.insert(make_pair(expr.expr2->table, p.first));
                                ans.insert(st);
                            }
                        }
                        else if (expr.op_char == '>')
                        {
                            Type *t = new Type_int(false, 0x7fffffff);
                            std::vector<RID> vec = index->SearchRangeEntry(data, t);

                            for (auto rid : vec)
                            {
                                RM_Record rec;
                                nameSt.find(expr.expr->table)->second->rmfh->GetRec(rid, rec);

                                if (*((Type_int *)rec.get(lit)) == *(Type_int *)data)
                                {
                                    rec.clear();
                                    continue;
                                }

                                rec.clear();
                                std::map<std::string, RID>st;
                                st.insert(make_pair(expr.expr->table, rid));
                                st.insert(make_pair(expr.expr2->table, p.first));
                                ans.insert(st);
                            }
                        }

                        break;

                    case hsql::Expr::LESS_EQ:
                    {
                        Type *t = new Type_int(false, 0x80000000);
                        std::vector<RID> vec = index->SearchRangeEntry(t, data);

                        for (auto rid : vec)
                        {
                            std::map<std::string, RID>st;
                            st.insert(make_pair(expr.expr->table, rid));
                            st.insert(make_pair(expr.expr2->table, p.first));
                            ans.insert(st);
                        }
                    }
                    break;

                    case hsql::Expr::GREATER_EQ:
                    {
                        Type *t = new Type_int(false, 0x7fffffff);
                        std::vector<RID> vec = index->SearchRangeEntry(data, t);

                        for (auto rid : vec)
                        {
                            std::map<std::string, RID>st;
                            st.insert(make_pair(expr.expr->table, rid));
                            st.insert(make_pair(expr.expr2->table, p.first));
                            ans.insert(st);
                        }
                    }
                    break;

                    default:
                        fprintf(stderr, "Unsupported Select Expr.\n");
                        return Success;
                }
            }
        }
        else if (tleft == 0 && tright == 6)
        {
            for (auto p : clist)
            {
                if (!data->set(p.second.c_str(), p.second.length()))
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
                                std::map<std::string, RID>st;
                                st.insert(make_pair(expr.expr->table, rid));
                                st.insert(make_pair(expr.expr2->table, p.first));
                                ans.insert(st);
                            }
                        }

                        break;

                    default:
                        fprintf(stderr, "Unsupported Select Expr.\n");
                        return Error;
                }
            }
        }
        else
        {
            fprintf(stderr, "The Expr Type is error.\n");
            return Error;
        }

        return Success;

    }

    RC selectRecord(std::vector<hsql::TableRef *>names, std::vector<hsql::Expr *> &fields, hsql::Expr *wheres)
    {
        if (curdb.empty())
        {
            fprintf(stderr, "There is no current database\n");
            return Error;
        }

        bf::path workPath = bf::current_path() / curdb;
        std::ifstream fi((workPath / configFile).string(), std::fstream::in);
        std::string buf;
        int f = 0;

        while (getline(fi, buf))
        {
            for (hsql::TableRef * tab : names)
            {
                if (strcmp(buf.c_str(), tab->name) == 0)
                {
                    bf::path path = workPath / tab->name;

                    if (bf::exists(path) && bf::is_directory(path))
                        f++;
                }
            }
        }

        fi.close();

        if (f != names.size())
        {
            fprintf(stderr, "Tables doesn't exist\n");
            return Error;
        }

        std::map<std::string, TM_Manager *> nameSt;
        std::map<std::string, std::map<string, int> >headSt;

        for (hsql::TableRef * tab : names)
        {

            bf::path path = workPath / tab->name;

            auto it = tbsta.find(path);

            if (it == tbsta.end())
            {
                tbsta.insert(make_pair(path, new TM_Manager(fm, bpm, path)));
                it = tbsta.find(path);
            }

            nameSt.insert(make_pair(tab->name, it->second));
            headSt.insert(make_pair(tab->name, it->second->makeHeadMap()));

        }

        std::set<std::map<std::string, RID> >set;

        if (!wheres)
        {
            set.insert(std::map<std::string, RID>());
        }
        else if (getSet(*wheres, nameSt, headSt, set) == Error)return Error;

        for (auto it = set.begin(); it != set.end(); it++)
        {
            for (hsql::TableRef * tab : names)
            {
                if (it->find(tab->name) == it->end())
                {
                    auto data = nameSt.find(tab->name)->second->rmfh->ListRec();

                    for (auto rec : data)
                    {
                        auto st = *it;
                        st.insert(make_pair(tab->name, rec.first));
                        set.insert(st);
                        rec.second.clear();
                    }
                }
            }
        }

        std::map<pair<std::string, std::string>, int>mi, ma, num;
        std::map<pair<std::string, std::string>, long long>sum;
        bool func = false;
        int starsize = 0;

        for (auto st : set)
        {
            bool f = true;

            for (hsql::TableRef * tab : names)
            {
                if (st.find(tab->name) == st.end())
                {
                    f = false;
                    break;
                }
            }

            if (!f)continue;

            for (hsql::Expr * expr : fields)
            {
                switch (expr->type)
                {
                    case hsql::kExprStar:
                        for (hsql::TableRef * tab : names)
                        {
                            RM_Record rec;
                            nameSt.find(tab->name)->second->rmfh->GetRec(st.find(tab->name)->second, rec);
                            rec.print();
                            starsize += rec.getSize();
                            rec.clear();
                        }

                        break;

                    case hsql::kExprColumnRef:
                    {
                        auto itt = headSt.find(expr->table);

                        if (itt == headSt.end())
                        {
                            fprintf(stderr, "Table %s is not found.\n", expr->table);
                            return Error;
                        }

                        RM_Record rec;
                        nameSt.find(expr->table)->second->rmfh->GetRec(st.find(expr->table)->second, rec);
                        const std::map<string, int> &st = itt->second;
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
                        auto itt = headSt.find(expr->expr->table);

                        if (itt == headSt.end())
                        {
                            fprintf(stderr, "Table %s is not found.\n", expr->expr->table);
                            return Error;
                        }

                        RM_Record rec;
                        nameSt.find(expr->expr->table)->second->rmfh->GetRec(st.find(expr->expr->table)->second, rec);
                        const std::map<string, int> &st = itt->second;
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

                        auto tmp = ma.begin();
                        sum[make_pair(expr->expr->table, expr->expr->name)] += ((Type_int *)t)->getValue();
                        num[make_pair(expr->expr->table, expr->expr->name)] ++;

                        if ((tmp = ma.find(make_pair(expr->expr->table, expr->expr->name))) == ma.end())
                            ma.insert(make_pair(make_pair(expr->expr->table, expr->expr->name), ((Type_int *)t)->getValue()));
                        else
                            tmp->second = std::max(it->second, ((Type_int *)t)->getValue());

                        if ((tmp = mi.find(make_pair(expr->expr->table, expr->expr->name))) == mi.end())
                            mi.insert(make_pair(make_pair(expr->expr->table, expr->expr->name), ((Type_int *)t)->getValue()));
                        else
                            tmp->second = std::min(it->second, ((Type_int *)t)->getValue());
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
                        for (int i = 0; i < starsize; i++)printf("|  | ");

                        break;

                    case hsql::kExprColumnRef:

                        printf("|  | ");

                        break;

                    case hsql::kExprFunctionRef:
                    {
                        std::string f = expr->name;

                        if (f == "AVG")
                        {
                            printf("| %s(%s.%s) = %.2lf | ", expr->name, expr->expr->table, expr->expr->name, double(sum[make_pair(expr->expr->table, expr->expr->name)]) / num[make_pair(expr->expr->table, expr->expr->name)]);
                        }
                        else if (f == "SUM")
                        {
                            printf("| %s(%s.%s) = %lld | ", expr->name, expr->expr->table, expr->expr->name, sum[make_pair(expr->expr->table, expr->expr->name)]);
                        }
                        else if (f == "MAX")
                        {
                            printf("| %s(%s.%s) = %d | ", expr->name, expr->expr->table, expr->expr->name, ma[make_pair(expr->expr->table, expr->expr->name)]);
                        }
                        else if (f == "MIN")
                        {
                            printf("| %s(%s.%s) = %d | ", expr->name, expr->expr->table, expr->expr->name, mi[make_pair(expr->expr->table, expr->expr->name)]);
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

    }

};
SM_Manager *SM_Manager::m_instance = NULL;
SM_Manager::CGarbo SM_Manager::Garbo = SM_Manager::Garbo;
#endif
