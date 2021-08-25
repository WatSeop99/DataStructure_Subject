#pragma once

#include "FileType.h"
#include "SortedLinkedList.h"

class FolderType {
private:
	std::string folName;
	std::string folPath;
	std::string folCreateTime;
	LinkedList<FolderType>* subFolder;
	LinkedList<FileType>* subFile;
	int subFolNum;
	int subFilNum;
public:
	FolderType();
	~FolderType();

	void SetRecordFromKB();
	void SetName(std::string _name) { folName = _name; }
	void SetPath(std::string _path) { folPath = _path; }
	void SetCreateTime(std::string _time) { folCreateTime = _time; }
	void GenCreateTime();
	std::string GetName() const { return folName; }
	std::string GetPath() const { return folPath; }
	std::string GetCreateTime() const { return folCreateTime; }
	int GetSubFolderNum() const { return subFolNum; }
	int GetSubFileNum() const { return subFilNum; }
	FolderType& operator=(const FolderType& data);
	bool operator>(const FolderType& data) { return folName > data.folName; }
	bool operator<(const FolderType& data) { return folName < data.folName; }
	bool operator==(const FolderType& data) { return folName == data.folName; }
	friend std::ostream& operator<<(std::ostream& os, const FolderType& data);
	bool AddSubFolder();
	bool AddSubFile();
	bool DeleteSubFolder();
	bool DeleteSubFile();
	bool RetrieveFolderByName();
	bool RetrieveFileByName();
	void DisplayFolderInfo();
	void DisplaySubFolder();
	void DisplaySubFile();
};