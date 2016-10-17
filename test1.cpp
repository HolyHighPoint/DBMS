#include <bufmanager/BufPageManager.h>
#include <fileio/FileManager.h>
#include <utils/pagedef.h>
#include <iostream>
#include "rm_filehandle.h"
#include "rm_manager.h"
#include "rm_record.h"

int main()
{
    MyBitMap::initConst();
    FileManager *fm = new FileManager();
    BufPageManager *bpm = new BufPageManager(fm);
    RM_Manager *rmm = new RM_Manager(fm, bpm);
    RM_FileHandle *rmfh = new RM_FileHandle();
    rmm->CreateFile("testfile.txt");
    rmm->OpenFile("testfile.txt", rmfh);
    RM_Record a, b, c;
    RID rid;
    a.push_back(new RM_Type_int(false, 1));
    a.push_back(new RM_Type_varchar<>(false, "hello", 5));
    a.push_back(new RM_Type_int(false, 5));
    a.push_back(new RM_Type_varchar<>(false, "world", 5));
    a.push_back(new RM_Type_int(true));
    a.push_back(new RM_Type_int(false, 2014011303));
    a.push_back(new RM_Type_varchar<>(false, "123", 3));
    a.push_back(new RM_Type_varchar<>(true));
    rmfh->InsertRec(a, rid);
    Byte byte = a.toByte();
    for(int i=0;i<byte.length;i++)
    {
        printf("%02d ", i);
    }
    printf("\n");
    for(int i=0;i<byte.length;i++)
    {
        printf("%02x ", byte.a[i]);
    }
    printf("\n");
    b.push_back(new RM_Type_int());
    b.push_back(new RM_Type_varchar<>());
    b.push_back(new RM_Type_int());
    b.push_back(new RM_Type_varchar<>());
    b.push_back(new RM_Type_int());
    b.push_back(new RM_Type_int());
    b.push_back(new RM_Type_varchar<>());
    b.push_back(new RM_Type_varchar<>());
    rmfh->GetRec(rid, b);
    b.print();
    rmm->CloseFile(rmfh);
    rmm->OpenFile("testfile.txt", rmfh);
    c.push_back(new RM_Type_int());
    c.push_back(new RM_Type_varchar<>());
    c.push_back(new RM_Type_int());
    c.push_back(new RM_Type_varchar<>());
    c.push_back(new RM_Type_int());
    c.push_back(new RM_Type_int());
    c.push_back(new RM_Type_varchar<>());
    c.push_back(new RM_Type_varchar<>());
    rmfh->GetRec(rid, c);
    c.print();
    rmm->CloseFile(rmfh);
}
