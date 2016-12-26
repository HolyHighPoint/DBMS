#include <bufmanager/BufPageManager.h>
#include <fileio/FileManager.h>
#include <utils/pagedef.h>
#include <iostream>
#include <vector>
#include "rm_filehandle.h"
#include "rm_manager.h"
#include "rm_record.h"
#include "ix_manager.h"
using namespace std;

int main()
{
    MyBitMap::initConst();
    FileManager *fm = new FileManager();
    BufPageManager *bpm = new BufPageManager(fm);
    RM_Manager *rmm = new RM_Manager(fm, bpm);
    RM_FileHandle *rmfh = new RM_FileHandle();
    rmm->CreateFile("test.db");
    rmm->OpenFile("test.db", rmfh);
    IX_Manager *ixm1 = new IX_Manager("test_1.db", true, new Type_int());
    IX_Manager *ixm2 = new IX_Manager("test_2.db", false, new Type_varchar<64>());
    IX_Manager *ixm3 = new IX_Manager("test_3.db", false, new Type_int());
    RM_Record a[10], c;
    c.push_back(new Type_int());
    c.push_back(new Type_varchar<>());
    c.push_back(new Type_int());
    c.push_back(new Type_varchar<>());
    c.push_back(new Type_int());
    c.push_back(new Type_int());
    c.push_back(new Type_varchar<>());
    c.push_back(new Type_varchar<>( ));
    RID rid[10];
    char str[10][3] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};

    for (int i = 0; i < 10; i++)
    {
        a[i].push_back(new Type_int(false, i));
        a[i].push_back(new Type_varchar<>(false, "hello", 5));
        a[i].push_back(new Type_int(false, i % 2));
        a[i].push_back(new Type_varchar<>(false, "world", 5));
        a[i].push_back(new Type_int(true));
        a[i].push_back(new Type_int(false, 2014011303));
        a[i].push_back(new Type_varchar<>(false, str[i], 3));
        a[i].push_back(new Type_varchar<>(true));
        rmfh->InsertRec(a[i], rid[i]);
        ixm1->InsertEntry(new Type_int(false, i), rid[i]);
        ixm2->InsertEntry(new Type_varchar<>(false, str[i], 3), rid[i]);
        ixm3->InsertEntry(new Type_int(false, i % 2), rid[i]);
    }

    vector<RID> ans = ixm1->SearchEntry(new Type_int(false, 5));

    for (int i = 0; i < ans.size(); i++)
    {
        rmfh->GetRec(ans[i], c);
        c.print();
    }

    ans = ixm2->SearchEntry(new Type_varchar<>(false, str[6], 3));

    for (int i = 0; i < ans.size(); i++)
    {
        rmfh->GetRec(ans[i], c);
        c.print();
    }

    ans = ixm3->SearchEntry(new Type_int(false, 0));

    for (int i = 0; i < ans.size(); i++)
    {
        rmfh->GetRec(ans[i], c);
        c.print();
    }

    printf("\n\n");
    ixm1->DeleteEntry(new Type_int(false, 4), rid[4]);
    ixm2->DeleteEntry(new Type_varchar<>(false, str[4], 3), rid[4]);
    ixm3->DeleteEntry(new Type_int(false, 0), rid[4]);
    ans = ixm1->SearchEntry(new Type_int(false, 4));

    for (int i = 0; i < ans.size(); i++)
    {
        rmfh->GetRec(ans[i], c);
        c.print();
    }

    ans = ixm2->SearchEntry(new Type_varchar<>(false, str[4], 3));

    for (int i = 0; i < ans.size(); i++)
    {
        rmfh->GetRec(ans[i], c);
        c.print();
    }

    ans = ixm3->SearchEntry(new Type_int(false, 0));

    for (int i = 0; i < ans.size(); i++)
    {
        rmfh->GetRec(ans[i], c);
        c.print();
    }

    rmm->CloseFile(rmfh);
}
