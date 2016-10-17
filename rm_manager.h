#ifndef RM_MANAGER_H
#define RM_MANAGER_H
#include "rc.h"
#include <bufmanager/BufPageManager.h>
#include <fileio/FileManager.h>
#include "rm_filehandle.h"
class RM_Manager
{
private:
    FileManager *fm;
    BufPageManager *bpm;
public:
    RM_Manager(FileManager *_fm, BufPageManager *_bpm)
    {
        fm = _fm;
        bpm = _bpm;
    }
    ~RM_Manager()
    {
    }
    RC CreateFile(const char *fileName)
    {
        if (fm->createFile(fileName))
        {
            return Success;
        }
        else
        {
            return Error;
        }
    }
    RC OpenFile(const char *fileName, RM_FileHandle *fileHandle)
    {
        int fileId;
        bool flag = fm->openFile(fileName, fileId);
        fileHandle->init(bpm, fileId);
        if (flag)
        {
            return Success;
        }
        else
        {
            return Error;
        }
    }
    RC CloseFile(RM_FileHandle *fileHandle)
    {
        int fileId = fileHandle->getFileId();
        bpm->close();
        if (fm->closeFile(fileId) == 0)
        {
            return Success;
        }
        else
        {
            return Error;
        }
    }
};
#endif
