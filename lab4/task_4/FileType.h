#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <sstream>
#include <iomanip>

class FileType {
private:
	std::string fileName;
	std::string filePath;
	std::string fileCreateTime;
	std::ifstream inFile;
	std::ofstream outFile;
public:
	FileType(const FileType& data);
	~FileType();

	void SetRecordFromKB();
	void SetName(std::string _name) { fileName = _name; }
	void SetPath(std::string _path) { filePath = _path; }
	void SetCreateTime(std::string _time) { fileCreateTime = _time; }
	void GenCreateTime();
	std::string GetName() const { return fileName; }
	std::string GetPath() const { return filePath; }
	std::string GetCreateTime() const { return fileCreateTime; }
	FileType& operator=(const FileType& data);
	bool operator>(const FileType& data) { return fileName > data.fileName; }
	bool operator<(const FileType& data) { return fileName < data.fileName; }
	bool operator==(const FileType& data) { return fileName == data.fileName; }
	friend std::ostream& operator<<(std::ostream& os, const FileType& data);
	bool OpenFile(std::string _file);
	bool WriteFile(std::string _file, int command);
	void DisplayFileInfo();
};