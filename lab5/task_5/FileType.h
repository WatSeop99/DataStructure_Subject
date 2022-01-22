#pragma once

#include <iostream>
#include <string>
#include <ctime>
#include <sstream>
#include <iomanip>
#include "TextFile.h"
#include "ImageFile.h"
#include "MusicFile.h"

class FileType {
private:
	std::string fileName;
	std::string filePath;
	std::string fileCreateTime;
	ItemType* fileContents;
	int fileType;
public:
	FileType(int type = 0);
	FileType(const FileType& data);
	~FileType() { if (fileContents) delete fileContents; }

	void SetRecordFromKB();
	void SetName(std::string _name) { fileName = _name; }
	void SetPath(std::string _path) { filePath = _path; }
	void SetCreateTime(std::string _time) { fileCreateTime = _time; }
	void SetType(int _type) { fileType = _type; }
	void GenCreateTime();
	std::string GetName() const { return fileName; }
	std::string GetPath() const { return filePath; }
	std::string GetCreateTime() const { return fileCreateTime; }
	int GetType() const { return fileType; }
	FileType& operator=(const FileType& data);
	bool operator>(const FileType& data) { return fileName.compare(data.fileName) > 0; }
	bool operator<(const FileType& data) { return fileName.compare(data.fileName) < 0;; }
	bool operator==(const FileType& data) { return (fileName.compare(data.fileName) == 0) && (fileType == data.fileType); }
	friend bool operator==(const FileType& data1, const FileType& data2);
	friend std::ostream& operator<<(std::ostream& os, const FileType& data);
	bool OpenFile();
	void DisplayFileInfo();
};