#ifndef RM_MANAGER_H
#define RM_MANAGER_H
#include "rc.h";
#include <stdio.h>
class RM_Manager {
private:
	FileManager *fm;
	BufPageManager* bpm;
public:
	RM_Manager(FileManager &pfm) {
		fm = pfm;
		bpm = new BufPageManager(fm);
	};
	~RM_Manager() {
		bpm->close();
	};
	RC CreateFile(const char *fileName, int recordSize) {
		if (fm->createFile(fileName)) { return Success; }
		else { return Error; }
	};
	RC DestroyFile(const char *fileName) {
		if (remove(fileName) == 0) { return Success; }
		else { return Error; }
	};
	RC OpenFile(const char *fileName, RM_FileHandle &fileHandle) {
		int fileId;
		bool flag;
		flag = fm->openFile(fileName, fileId);
		fileHandle->setFileId(fileId);// TBD
		if (flag) { return Success; }
		else { return Error; }
	};
	RC CloseFile(RM_FileHandle &fileHandle) {
		fileId = fileHandle->getFileId();//TBD
		if (fm->closeFile(fileId) == 0) { return Success;}
		else { return Error; }
	};
};
#endif