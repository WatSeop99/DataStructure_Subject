#include "FileType.h"

FileType::FileType(const FileType& data) {
	fileName = data.fileName;
	filePath = data.filePath;
	fileCreateTime = data.fileCreateTime;
}

void FileType::SetRecordFromKB() {
	std::string name;
	std::cout << "\t Enter file Name : ";
	std::cin >> name;
	SetName(name);
}

void FileType::GenCreateTime() {
	using namespace std;

	time_t curr_time;
	struct tm* curr_tm;
	curr_time = time(NULL);
	curr_tm = localtime(&curr_time);
	string year = to_string(curr_tm->tm_year + 1900) + "년 ";
	string month = to_string(curr_tm->tm_mon + 1) + "월 ";
	string day = to_string(curr_tm->tm_mday) + "일 / ";
	string hour = to_string(curr_tm->tm_hour) + "시 ";
	string minute = to_string(curr_tm->tm_min) + "분 ";
	string second = to_string(curr_tm->tm_sec) + "초 ";
	string curTime = year + month + day + hour + minute + second;
	SetCreateTime(curTime);
}

FileType& FileType::operator=(const FileType& data) {
	fileName = data.fileName;
	filePath = data.filePath;
	fileCreateTime = data.fileCreateTime;
	return *this;
}

std::ostream& operator<<(std::ostream& os, const FileType& data) {
	os << data.fileName;
	return os;
}

bool FileType::OpenFile(std::string file) {
	inFile.open(file);
	if (!inFile) {
		std::cout << "Rfile is not open." << std::endl;
		return false;
	}
	std::string str;
	std::cout << std::endl << "\t == Contents == " << std::endl;
	while (getline(inFile, str))
		std::cout << str << std::endl;
	inFile.close();
	return true;
}

bool FileType::WriteFile(std::string file, int command) {
	if (command == 2) outFile.open(file);
	else if (command == 3) {
		outFile.open(file, std::ios::app);
		if (!outFile) {
			std::cout << "Wfile is not open." << std::endl;
			return false;
		}
	}
	std::string str;
	std::cout << std::endl << "\t Write contents what you want (q to quit): ";
	getline(std::cin, str);
	while (str != "q") {
		outFile << str << '\n';
		getline(std::cin, str);
	}
	outFile.close();
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