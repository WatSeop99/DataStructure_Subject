#pragma warning(disable : 4996)

#include "FileType.h"

FileType::FileType(int type) {
	fileName = "";
	filePath = "";
	fileType = type;
	GenCreateTime();
	fileContents = nullptr;
}

FileType::FileType(const FileType& data) {
	fileName = data.fileName;
	filePath = data.filePath;
	fileCreateTime = data.fileCreateTime;
	fileType = data.fileType;
	switch (fileType) {
	case 0:
		fileContents = new TextFile;
		break;
	case 1:
		fileContents = new ImageFile;
		break;
	case 2:
		fileContents = new MusicFile;
		break;
	}
}

void FileType::SetRecordFromKB() {
	std::string name;
	std::cout << "\t Enter file name : ";
	std::cin >> name;
	SetName(name);
}

void FileType::GenCreateTime() {
	time_t curr_time;
	struct tm* curr_tm;
	curr_time = time(NULL);
	curr_tm = localtime(&curr_time);
	std::string year = std::to_string(curr_tm->tm_year + 1900) + "년 ";
	std::string month = std::to_string(curr_tm->tm_mon + 1) + "월 ";
	std::string day = std::to_string(curr_tm->tm_mday) + "일 / ";
	std::string hour = std::to_string(curr_tm->tm_hour) + "시 ";
	std::string minute = std::to_string(curr_tm->tm_min) + "분 ";
	std::string second = std::to_string(curr_tm->tm_sec) + "초 ";
	std::string curTime = year + month + day + hour + minute + second;
	fileCreateTime = curTime;
}

FileType& FileType::operator=(const FileType& data) {
	fileName = data.fileName;
	filePath = data.filePath;
	fileCreateTime = data.fileCreateTime;
	fileType = data.fileType;
	if (fileContents) delete fileContents;
	switch (fileType) {
	case 0:
		fileContents = new TextFile;
		break;
	case 1:
		fileContents = new ImageFile;
		break;
	case 2:
		fileContents = new MusicFile;
		break;
	}
	return *this;
}

bool operator==(const FileType& data1, const FileType& data2) {
	return (data1.fileName.compare(data2.fileName) == 0) && (data1.GetType() == data2.GetType());
}

std::ostream& operator<<(std::ostream& os, const FileType& data) {
	os << data.fileName;
	return os;
}

bool FileType::OpenFile() {
	if (fileContents == nullptr) return false;
	fileContents->Run(fileName);
	return true;
}

void FileType::DisplayFileInfo() {
	using namespace std;

	cout << endl;
	cout << "\t ======= Current File Info =======" << endl;
	cout << "\t    file name : " << fileName << endl;
	cout << "\t    file path : " << filePath << endl;
	cout << "\t    created time : " << fileCreateTime << endl;
	cout << "\t =================================" << endl << endl;
}