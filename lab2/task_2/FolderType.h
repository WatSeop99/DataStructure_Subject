#pragma once

#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include <sstream>
#include "SortedList.h"

class SortedList;

class FolderType {
private:
	SortedList* SubList;
	std::string folName;
	std::string folPath;
	std::string folCRTime;
	int folSize, subFolNum;
public:
	FolderType(std::string _name = "\0", std::string _path = "\0") : folName(_name) {
		folSize = 1;
		subFolNum = 0;
		folPath = _path;
		GenCreateTime();
		SubList = nullptr;
	}
	~FolderType() { if (SubList) delete SubList; }

	void SetRecordFromKB();
	void SetName(std::string _name) { folName = _name; }
	void SetPath(std::string _path) { folPath = _path; }
	void SetCreateTime(std::string _time) { folCRTime = _time; }
	void GenCreateTime();
	std::string GetName() const { return folName; }
	std::string GetPath() const { return folPath; }
	std::string GetCreateTime() const { return folCRTime; }
	int GetSubFolderNum() const { return subFolNum; }
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