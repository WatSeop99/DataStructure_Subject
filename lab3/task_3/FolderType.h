#pragma once

#include <iostream>
#include <string>
#include <ctime>
#include <sstream>
#include <iomanip>
#include "SortedList.h"

class FolderType {
private:
	std::string folName;
	std::string folPath;
	std::string folCreateTime;
	SortedList<FolderType>* SubFdList;
	int SubFolderNum;
public:
	FolderType(std::string _name = "\0", std::string _path = "\0", std::string _time = "\0") : folName(_name), folPath(_path), folCreateTime(_time) {
		SubFdList = nullptr;
		SubFolderNum = 0;
	}
	~FolderType();

	void SetRecordFromKB();
	void SetName(std::string _name) { folName = _name; }
	void SetPath(std::string _path) { folPath = _path; }
	void SetCreateTime(std::string _time) { folCreateTime = _time; }
	void GenCreateTime();
	std::string GetName() const { return folName; }
	std::string GetPath() const { return folPath; }
	std::string GetCreateTime() const { return folCreateTime; }
	int GetSubFolderNum() const { return SubFolderNum; }
	FolderType& operator=(const FolderType& data);
	bool operator>(const FolderType& data) { return folName > data.folName ? true : false; }
	bool operator<(const FolderType& data) { return folName < data.folName ? true : false; }
	bool operator==(const FolderType& data) { return folName == data.folName ? true : false; }
	bool AddSubFolder();
	bool DeleteSubFolder();
	bool RetrieveFolderByName();
	void DisplayFolderInfo();
	FolderType* GoToSubFolder();
};