#ifndef IX_MANAGER_H
#define IX_MANAGER_H

#include "type.h"
#include "rc.h"
#include "bptree.h"
#include <algorithm>
#include <fstream>
#include <string>

class IX_Manager {
private:
    bool fexists(const char *filename) {
      std::ifstream ifile(filename);
      return (bool)ifile;
    }
    bptree::bplus_tree<Type_int, RID> *bptree_int;
    bptree::bplus_tree<Type_varchar<64>, RID> *bptree_str_64;
    bptree::bplus_tree<RID, std::pair<RID, RID> > *bptree_rid;
public:
    IX_Manager (const char *filename, bool unique, Type *type)
    {
        if(dynamic_cast<Type_int*>(type) != NULL)
        {
            bptree_int = new bptree::bplus_tree<Type_int, RID>(filename, !fexists(filename));
            bptree_str_64 = NULL;
        }
        if(dynamic_cast<Type_varchar<64>*>(type) != NULL)
        {
            bptree_str_64 = new bptree::bplus_tree<Type_varchar<64>, RID>(filename, !fexists(filename));
            bptree_int = NULL;
        }
        if(!unique)
        {
            std::string tmp = "deque_";
            tmp += filename;
            bptree_rid = new bptree::bplus_tree<RID, std::pair<RID, RID> >(tmp.c_str(), !fexists(tmp.c_str()));
        }else bptree_rid = NULL;
    }

    ~IX_Manager ()
    {
        if(bptree_int)delete bptree_int;
        if(bptree_str_64)delete bptree_str_64;
        if(bptree_rid)delete bptree_rid;
    }

    RC InsertEntry (Type *data, const RID &rid)
    {
        if(bptree_int)
        {
            int ret = bptree_int->insert(*(Type_int*)data, rid);
            if(ret)
            {
                if(!bptree_rid)return Error;
                RID first;
                bptree_int->search(*(Type_int*)data, &first);
                if(first == RID())
                {
                }
                std::pair<RID, RID> link;
                bptree_rid->search(rid, &link);
                link.first = rid;
                bptree_rid->update(first, link);
                bptree_rid->insert(rid, std::make_pair(RID(), first));
            }
            else
            {
                if(bptree_rid)
                    bptree_rid->insert(rid, std::make_pair(RID(), RID()));
            }
        }
        if(bptree_str_64)
        {
            int ret = bptree_str_64->insert(*(Type_varchar<64>*)data, rid);
            if(ret)
            {
                if(!bptree_rid)return Error;
                RID first;
                bptree_str_64->search(*(Type_varchar<64>*)data, &first);
                std::pair<RID, RID> link;
                bptree_rid->search(rid, &link);
                link.first = rid;
                bptree_rid->update(first, link);
                bptree_rid->insert(rid, std::make_pair(RID(), first));
            }
            else
            {
                if(bptree_rid)
                    bptree_rid->insert(rid, std::make_pair(RID(), RID()));
            }
        }
    }

    RC DeleteEntry (Type *data, const RID &rid)
    {

    }
};

#endif

