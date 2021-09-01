#include "FileType.h"

FileType::FileType(int type = 0) {
	fileName = "\0";
	filePath = "\0";
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
	std::string _name;
	std::cout << "\t  파일이름을 입력 : ";
	std::cin >> _name;
	fileName = _name;
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

std::ostream& operator<<(std::ostream& os, const FileType& data) {
	os << data.fileName;
	return os;
}

bool FileType::OpenFile() {
	if (fileContents == nullptr) return false;

}

void FileType::DisplayFileInfo() {

}