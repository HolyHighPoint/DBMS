#include <bufmanager/BufPageManager.h>
#include <fileio/FileManager.h>
#include <utils/pagedef.h>
#include <iostream>
#include "rm_filehandle.h"
#include "rm_manager.h"
#include "rm_record.h"
#include <map>
using namespace std;
char str[1024], str1[1024], str2[1024];
void randStr(int length)
{
    for(int i=0;i<length;i++)str[i] = rand()%26+'a';
    str[length] = 0;
}
bool operator < (const RID &a, const RID &b)
{
    if(a.pageId == b.pageId)return a.rowId < b.rowId;else return a.pageId < b.pageId;
}

bool operator == (const RID &a, const RID &b)
{
    return a.pageId == b.pageId && a.rowId == b.rowId;
}

int main()
{
    srand(time(NULL));
    MyBitMap::initConst();
    FileManager *fm = new FileManager();
    BufPageManager *bpm = new BufPageManager(fm);
    RM_Manager *rmm = new RM_Manager(fm, bpm);
    RM_FileHandle *rmfh = new RM_FileHandle();
    rmm->CreateFile("testfile.txt");
    rmm->OpenFile("testfile.txt", rmfh);
    map<RID, RM_Record> sta;
    for(int i=0;i<200000;i++)
    {
        if(rand()%3 == 0)
        {
            for(auto &k : sta)
            {
                if(rand()%100 == 0)
                {
                    rmfh->DeleteRec(k.first);
                    sta.erase(sta.find(k.first));
                    break;
                }
            }
        }
        else
        {
            RM_Record a;
            RID rid;
            a.push_back(new RM_Type_int(rand()%2, rand()%RAND_MAX));
            int len = rand()%65;randStr(len);
            a.push_back(new RM_Type_varchar<>(rand()%2, str, len));
            a.push_back(new RM_Type_int(rand()%2, rand()%RAND_MAX));
            len = rand()%65;randStr(len);
            a.push_back(new RM_Type_varchar<>(rand()%2, str, len));
            a.push_back(new RM_Type_int(rand()%2, rand()%RAND_MAX));
            a.push_back(new RM_Type_int(rand()%2, rand()%RAND_MAX));
            len = rand()%65;randStr(len);
            a.push_back(new RM_Type_varchar<>(rand()%2, str, len));
            a.push_back(new RM_Type_varchar<>(rand()%2, str, len));
            if(rmfh->InsertRec(a, rid) == Error)
            {
                rmfh->InsertRec(a, rid);
                printf("Error\n");
                return -1;
            }
            sta.insert(make_pair(rid, a));
        }
    }
    RM_Record b;
    b.push_back(new RM_Type_int());
    b.push_back(new RM_Type_varchar<>());
    b.push_back(new RM_Type_int());
    b.push_back(new RM_Type_varchar<>());
    b.push_back(new RM_Type_int());
    b.push_back(new RM_Type_int());
    b.push_back(new RM_Type_varchar<>());
    b.push_back(new RM_Type_varchar<>());
    int i=0;
    for(auto k : sta)
    {
        rmfh->GetRec(k.first, b);
        Byte x = k.second.toByte(), y = b.toByte();
        if(x.length != y.length)
        {
            k.second.print();
            b.print();
            printf("Error %d\n", i);
            return -1;
        }
        for(int i=0;i<x.length;i++)if(x.a[i] != y.a[i])
        {
            k.second.print();
            b.print();
            printf("Error %d\n", i);
            return -1;
        }
        i++;
    }
    auto list = rmfh->ListRec();
    i=0;
    for(auto k : list)
    {
        if(sta.find(k.first) == sta.end())
        {
            printf("Error %d %d\n", list.size(), sta.size());
            return -1;
        }
        b = sta.find(k.first)->second;
        Byte x = k.second.toByte(), y = b.toByte();
        if(x.length != y.length)
        {
            k.second.print();
            b.print();
            printf("Error %d\n", i);
            return -1;
        }
        for(int i=0;i<x.length;i++)if(x.a[i] != y.a[i])
        {
            k.second.print();
            b.print();
            printf("Error %d\n", i);
            return -1;
        }
        i++;
    }
    printf("Accept\n");
    rmm->CloseFile(rmfh);
}
