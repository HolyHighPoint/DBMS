#ifndef SM_MANAGER_H
#define SM_MANAGER_H
#include "rc.h"
#include <boost/filesystem.hpp>
#include <fstream>
#include <bufmanager/BufPageManager.h>
#include <fileio/FileManager.h>
#include <map>
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

    RC selectRecord(const char *name, std::vector<hsql::Expr *> &fields, hsql::Expr *wheres)
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

        return it->second->selectRecord(fields, wheres);

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

};
SM_Manager *SM_Manager::m_instance = NULL;
SM_Manager::CGarbo SM_Manager::Garbo = SM_Manager::Garbo;
#endif
