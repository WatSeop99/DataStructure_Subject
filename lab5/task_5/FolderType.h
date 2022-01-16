#pragma once

#include "FileType.h"
#include "LinkedList.h"

class FolderType {
private:
	std::string folderName;
	std::string folderPath;
	std::string folderCreateTime;
	LinkedList<FolderType>* subFolder;
	LinkedList<FileType>* subFile;
	int subFolderNum;
	int subFileNum;
public:
	FolderType();
	FolderType(const FolderType& data);
	~FolderType();

	void SetRecordFromKB();
	void SetName(std::string _name) { folderName = _name; }
	void SetPath(std::string _path) { folderPath = _path; }
	void SetCreateTime(std::string _time) { folderCreateTime = _time; }
	void GenCreateTime();
	std::string GetName() const { return folderName; }
	std::string GetPath() const { return folderPath; }
	std::string GetCreateTime() const { return folderCreateTime; }
	int GetSubFolderNum() const { return subFolderNum; }
	int GetSubFileNum() const { return subFileNum; }
	FolderType& operator=(const FolderType& data);
	bool operator>(const FolderType& data) { return folderName > data.folderName; }
	bool operator<(const FolderType& data) { return folderName < data.folderName; }
	bool operator==(const FolderType& data) { return folderName == data.folderName; }
	friend std::ostream& operator<<(std::ostream& os, const FolderType& data);
	bool AddSubFolder();
	bool AddSubFile();
	bool DeleteSubFolder();
	bool DeleteSubFile();
	bool CopyFolder(FolderType*& data, std::string name);
	bool CopyFile(FileType*& data, std::string name);
	bool PasteFolder(FolderType*& data);
	bool PasteFile(FileType*& data);
	bool RetrieveFolderByName(std::string name);
	bool RetrieveFolderByName(FolderType*& data);
	bool RetrieveFileByName(std::string name);
	bool RetrieveFileByName(FileType*& data);
	void DisplayFolderInfo();
	void DisplaySubFolder();
	void DisplaySubFile();
	FolderType* GoToSubFolder();
	FileType* OpenSubFile();
};