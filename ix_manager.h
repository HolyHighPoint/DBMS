#ifndef IX_MANAGER_H
#define IX_MANAGER_H

#include "type.h"
#include "rc.h"
#include "bptree.h"
#include <algorithm>
#include <fstream>
#include <string>

class IX_Manager
{
private:
    bool fexists(const char *filename)
    {
        std::ifstream ifile(filename);
        return (bool)ifile;
    }
    bptree::bplus_tree<Type_int, RID> *bptree_int;
    bptree::bplus_tree<Type_varchar<32>, RID> *bptree_str_32;
    bptree::bplus_tree<Type_varchar<64>, RID> *bptree_str_64;
    bptree::bplus_tree<Type_varchar<128>, RID> *bptree_str_128;
    bptree::bplus_tree<Type_varchar<256>, RID> *bptree_str_256;
    bptree::bplus_tree<RID, std::pair<RID, RID> > *bptree_rid;
public:
    IX_Manager (const char *filename, const char *deque_filename, Type *type)
    {
        bptree_int = NULL;
        bptree_str_32 = NULL;
        bptree_str_64 = NULL;
        bptree_str_128 = NULL;
        bptree_str_256 = NULL;
        bptree_rid = NULL;

        if (dynamic_cast<Type_int *>(type) != NULL)
        {
            bptree_int = new bptree::bplus_tree<Type_int, RID>(filename, !fexists(filename));
        }

        if (dynamic_cast<Type_varchar<32>*>(type) != NULL)
        {
            bptree_str_32 = new bptree::bplus_tree<Type_varchar<32>, RID>(filename, !fexists(filename));
        }

        if (dynamic_cast<Type_varchar<64>*>(type) != NULL)
        {
            bptree_str_64 = new bptree::bplus_tree<Type_varchar<64>, RID>(filename, !fexists(filename));
        }

        if (dynamic_cast<Type_varchar<128>*>(type) != NULL)
        {
            bptree_str_128 = new bptree::bplus_tree<Type_varchar<128>, RID>(filename, !fexists(filename));
        }

        if (dynamic_cast<Type_varchar<256>*>(type) != NULL)
        {
            bptree_str_256 = new bptree::bplus_tree<Type_varchar<256>, RID>(filename, !fexists(filename));
        }

        if (deque_filename)
        {
            bptree_rid = new bptree::bplus_tree<RID, std::pair<RID, RID> >(deque_filename, !fexists(deque_filename));
        }
    }

    ~IX_Manager ()
    {
        if (bptree_int)delete bptree_int;

        if (bptree_str_32)delete bptree_str_32;

        if (bptree_str_64)delete bptree_str_64;

        if (bptree_str_128)delete bptree_str_128;

        if (bptree_str_256)delete bptree_str_256;

        if (bptree_rid)delete bptree_rid;
    }

    RC InsertEntry (Type *data, const RID &rid)
    {
        if (bptree_int)
        {
            bptree_int->insert(*(Type_int *)data, rid);
            RID first;
            bptree_int->search(*(Type_int *)data, &first);

            if (first == RID())
            {
                bptree_int->update(*(Type_int *)data, rid);

                if (bptree_rid)bptree_rid->insert(rid, std::make_pair(RID(), RID()));

                return Success;
            }
            else if (first == rid)
            {
                if (bptree_rid)bptree_rid->insert(rid, std::make_pair(RID(), RID()));

                return Success;
            }
            else
            {
                if (!bptree_rid)return Error;

                std::pair<RID, RID> link;
                bptree_rid->search(first, &link);
                link.first = rid;
                bptree_rid->update(first, link);
                bptree_rid->insert(rid, std::make_pair(RID(), first));
                bptree_int->update(*(Type_int *)data, rid);
            }
        }

        if (bptree_str_32)
        {
            bptree_str_32->insert(*(Type_varchar<32> *)data, rid);
            RID first;
            bptree_str_32->search(*(Type_varchar<32> *)data, &first);

            if (first == RID())
            {
                bptree_str_32->update(*(Type_varchar<32> *)data, rid);

                if (bptree_rid)bptree_rid->insert(rid, std::make_pair(RID(), RID()));

                return Success;
            }
            else if (first == rid)
            {
                if (bptree_rid)bptree_rid->insert(rid, std::make_pair(RID(), RID()));

                return Success;
            }
            else
            {
                if (!bptree_rid)return Error;

                std::pair<RID, RID> link;
                bptree_rid->search(first, &link);
                link.first = rid;
                bptree_rid->update(first, link);
                bptree_rid->insert(rid, std::make_pair(RID(), first));
                bptree_str_32->update(*(Type_varchar<32> *)data, rid);
            }
        }


        if (bptree_str_64)
        {
            bptree_str_64->insert(*(Type_varchar<64> *)data, rid);
            RID first;
            bptree_str_64->search(*(Type_varchar<64> *)data, &first);

            if (first == RID())
            {
                bptree_str_64->update(*(Type_varchar<64> *)data, rid);

                if (bptree_rid)bptree_rid->insert(rid, std::make_pair(RID(), RID()));

                return Success;
            }
            else if (first == rid)
            {
                if (bptree_rid)bptree_rid->insert(rid, std::make_pair(RID(), RID()));

                return Success;
            }
            else
            {
                if (!bptree_rid)return Error;

                std::pair<RID, RID> link;
                bptree_rid->search(first, &link);
                link.first = rid;
                bptree_rid->update(first, link);
                bptree_rid->insert(rid, std::make_pair(RID(), first));
                bptree_str_64->update(*(Type_varchar<64> *)data, rid);
            }
        }

        if (bptree_str_128)
        {
            bptree_str_128->insert(*(Type_varchar<128> *)data, rid);
            RID first;
            bptree_str_128->search(*(Type_varchar<128> *)data, &first);

            if (first == RID())
            {
                bptree_str_128->update(*(Type_varchar<128> *)data, rid);

                if (bptree_rid)bptree_rid->insert(rid, std::make_pair(RID(), RID()));

                return Success;
            }
            else if (first == rid)
            {
                if (bptree_rid)bptree_rid->insert(rid, std::make_pair(RID(), RID()));

                return Success;
            }
            else
            {
                if (!bptree_rid)return Error;

                std::pair<RID, RID> link;
                bptree_rid->search(first, &link);
                link.first = rid;
                bptree_rid->update(first, link);
                bptree_rid->insert(rid, std::make_pair(RID(), first));
                bptree_str_128->update(*(Type_varchar<128> *)data, rid);
            }
        }

        if (bptree_str_256)
        {
            bptree_str_256->insert(*(Type_varchar<256> *)data, rid);
            RID first;
            bptree_str_256->search(*(Type_varchar<256> *)data, &first);

            if (first == RID())
            {
                bptree_str_256->update(*(Type_varchar<256> *)data, rid);

                if (bptree_rid)bptree_rid->insert(rid, std::make_pair(RID(), RID()));

                return Success;
            }
            else if (first == rid)
            {
                if (bptree_rid)bptree_rid->insert(rid, std::make_pair(RID(), RID()));

                return Success;
            }
            else
            {
                if (!bptree_rid)return Error;

                std::pair<RID, RID> link;
                bptree_rid->search(first, &link);
                link.first = rid;
                bptree_rid->update(first, link);
                bptree_rid->insert(rid, std::make_pair(RID(), first));
                bptree_str_256->update(*(Type_varchar<256> *)data, rid);
            }
        }


        return Success;
    }

    RC DeleteEntry (Type *data, const RID &rid)
    {
        if (bptree_int)
        {
            if (bptree_rid)
            {
                std::pair<RID, RID> link, next, pre;

                if (bptree_rid->search(rid, &link) != 0)return Error;

                if (link.first == RID())bptree_int->update(*(Type_int *)data, link.second);

                if (link.second != RID())
                {
                    bptree_rid->search(link.second, &next);
                    bptree_rid->update(link.second, make_pair(link.first, next.second));
                }

                if (link.first != RID())
                {
                    bptree_rid->search(link.first, &pre);
                    bptree_rid->update(link.first, make_pair(pre.first, link.second));
                }
            }
            else
            {
                if (bptree_int->update(*(Type_int *)data, RID()) != 0)return Error;
            }
        }

        if (bptree_str_32)
        {
            if (bptree_rid)
            {
                std::pair<RID, RID> link, next, pre;

                if (bptree_rid->search(rid, &link) != 0)return Error;

                if (link.first == RID())bptree_str_32->update(*(Type_varchar<32> *)data, link.second);

                if (link.second != RID())
                {
                    bptree_rid->search(link.second, &next);
                    bptree_rid->update(link.second, make_pair(link.first, next.second));
                }

                if (link.first != RID())
                {
                    bptree_rid->search(link.first, &pre);
                    bptree_rid->update(link.first, make_pair(pre.first, link.second));
                }
            }
            else
            {
                if (bptree_int->update(*(Type_int *)data, RID()) != 0)return Error;
            }
        }


        if (bptree_str_64)
        {
            if (bptree_rid)
            {
                std::pair<RID, RID> link, next, pre;

                if (bptree_rid->search(rid, &link) != 0)return Error;

                if (link.first == RID())bptree_str_64->update(*(Type_varchar<64> *)data, link.second);

                if (link.second != RID())
                {
                    bptree_rid->search(link.second, &next);
                    bptree_rid->update(link.second, make_pair(link.first, next.second));
                }

                if (link.first != RID())
                {
                    bptree_rid->search(link.first, &pre);
                    bptree_rid->update(link.first, make_pair(pre.first, link.second));
                }
            }
            else
            {
                if (bptree_int->update(*(Type_int *)data, RID()) != 0)return Error;
            }
        }

        if (bptree_str_128)
        {
            if (bptree_rid)
            {
                std::pair<RID, RID> link, next, pre;

                if (bptree_rid->search(rid, &link) != 0)return Error;

                if (link.first == RID())bptree_str_128->update(*(Type_varchar<128> *)data, link.second);

                if (link.second != RID())
                {
                    bptree_rid->search(link.second, &next);
                    bptree_rid->update(link.second, make_pair(link.first, next.second));
                }

                if (link.first != RID())
                {
                    bptree_rid->search(link.first, &pre);
                    bptree_rid->update(link.first, make_pair(pre.first, link.second));
                }
            }
            else
            {
                if (bptree_int->update(*(Type_int *)data, RID()) != 0)return Error;
            }
        }

        if (bptree_str_256)
        {
            if (bptree_rid)
            {
                std::pair<RID, RID> link, next, pre;

                if (bptree_rid->search(rid, &link) != 0)return Error;

                if (link.first == RID())bptree_str_256->update(*(Type_varchar<256> *)data, link.second);

                if (link.second != RID())
                {
                    bptree_rid->search(link.second, &next);
                    bptree_rid->update(link.second, make_pair(link.first, next.second));
                }

                if (link.first != RID())
                {
                    bptree_rid->search(link.first, &pre);
                    bptree_rid->update(link.first, make_pair(pre.first, link.second));
                }
            }
            else
            {
                if (bptree_int->update(*(Type_int *)data, RID()) != 0)return Error;
            }
        }

        return Success;
    }

    std::vector<RID> SearchEntry (Type *data)
    {
        std::vector<RID> ans;
        ans.clear();
        RID first;
        std::pair<RID, RID> t;

        if (bptree_int)
        {
            if (bptree_int->search(*(Type_int *)data, &first) != 0)return ans;
        }

        if (bptree_str_32)
        {
            if (bptree_str_32->search(*(Type_varchar<32> *)data, &first) != 0)return ans;
        }

        if (bptree_str_64)
        {
            if (bptree_str_64->search(*(Type_varchar<64> *)data, &first) != 0)return ans;
        }

        if (bptree_str_128)
        {
            if (bptree_str_128->search(*(Type_varchar<128> *)data, &first) != 0)return ans;
        }

        if (bptree_str_256)
        {
            if (bptree_str_256->search(*(Type_varchar<256> *)data, &first) != 0)return ans;
        }

        if (!bptree_rid)
        {
            if (first != RID()) ans.push_back(first);

            return ans;
        }

        for (RID i = first; i != RID(); bptree_rid->search(i, &t), i = t.second)
        {
            ans.push_back(i);
        }

        return ans;
    }

    std::vector<RID> SearchRangeEntry (Type *left, Type *right)
    {
        std::vector<RID> ans, tmp;
        ans.clear();
        std::pair<RID, RID> t;

        if (bptree_int)
        {
            tmp = bptree_int->search_range(*(Type_int *)left, *(Type_int *)right);
        }
        else
        {
            return ans;
        }

        if (!bptree_rid)
        {
            for (RID rid : tmp)
                if (rid != RID()) ans.push_back(rid);

            return ans;
        }

        for (RID rid : tmp)
            for (RID i = rid; i != RID(); bptree_rid->search(i, &t), i = t.second)
            {
                ans.push_back(i);
            }

        return ans;
    }
};

#endif

