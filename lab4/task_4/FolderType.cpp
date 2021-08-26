#include "FolderType.h"

FolderType::FolderType() : folName("\0"), folPath("\0") {
	subFolder = nullptr;
	subFile = nullptr;
	subFolNum = 0;
	subFilNum = 0;
	GenCreateTime();
}

FolderType::~FolderType() {
	if (subFolder) delete subFolder;
	if (subFile) delete subFile;
}

void FolderType::SetRecordFromKB() {
	std::string name;
	std::cout << "\t Enter folder Name : ";
	std::cin >> name;
	SetName(name);
}

void FolderType::GenCreateTime() {
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

FolderType& FolderType::operator=(const FolderType& data) {
	folName = data.folName;
	folPath = data.folPath;
	folCreateTime = data.folCreateTime;
	if (subFolNum != 0) subFolder = data.subFolder;
	if (subFilNum != 0) subFile = data.subFile;
	return *this;
}

std::ostream& operator<<(std::ostream& os, const FolderType& data) {
	os << data.folName;
	return os;
}

bool FolderType::AddSubFolder() {
	if (subFolder == nullptr) subFolder = new LinkedList<FolderType>;
	FolderType subfol;
	subfol.SetRecordFromKB();
	subfol.SetPath(folPath + '\\' + subfol.folName);
	subfol.GenCreateTime();
	if (subFolder->Add(subfol)) {
		std::cout << "\t Add success!" << std::endl;
		++subFolNum;
		return true;
	}
	else {
		std::cout << "\t Add fail!" << std::endl;
		return false;
	}
}

bool FolderType::AddSubFile() {
	if (subFile == nullptr) subFile = new LinkedList<FileType>;
	FileType subfil;
	subfil.SetRecordFromKB();
	subfil.SetPath(subfil.GetPath() + '\\' + subfil.GetName());
	if (subFile->Add(subfil)) {
		std::cout << "\t Add success!" << std::endl;
		++subFilNum;
		return true;
	}
	else {
		std::cout << "\t Add fail" << std::endl;
		return false;
	}
}

bool FolderType::DeleteSubFolder() {
	if (subFolder == nullptr) {
		std::cout << "\t ## NO SUBFOLDER ##" << std::endl;
		return false;
	}
	FolderType subfol;
	subfol.SetRecordFromKB();
	if (subFolder->Delete(subfol)) {
		std::cout << "\t Delete success!" << std::endl;
		--subFolNum;
		return true;
	}
	else {
		std::cout << "\t Delete fail!" << std::endl;
		return false;
	}
}

bool FolderType::DeleteSubFile() {
	if (subFile == nullptr)
	{
		std::cout << "\t ## NO SUBFILE ##" << std::endl;
		return false;
	}
	FileType subfil;
	subfil.SetRecordFromKB();
	if (subFile->Delete(subfil)) {
		std::cout << "\t Delete success!" << std::endl;
		--subFilNum;
		return true;
	}
	else {
		std::cout << "\t Delete fail!" << std::endl;
		return false;
	}
}

bool FolderType::RetrieveFolderByName() {
	if (subFolder == nullptr) {
		std::cout << "\t There is no list" << std::endl;
		return false;
	}
	FolderType temp;
	temp.SetRecordFromKB();
	if (subFolder->Get(temp)) {
		temp.DisplayFolderInfo();
		return true;
	}
	else {
		std::cout << "\t ## NOT FOUND ##" << std::endl;
		return false;
	}
}

bool FolderType::RetrieveFileByName() {
	if (subFile == nullptr) {
		std::cout << "\t There is no list" << std::endl;
		return false;
	}
	FileType temp;
	temp.SetRecordFromKB();
	if (subFile->Get(temp)) {
		temp.DisplayFileInfo();
		return true;
	}
	else {
		std::cout << "\t ## NOT FOUND ##" << std::endl;
		return false;
	}
}

void FolderType::DisplayFolderInfo() {
	using namespace std;

	cout << endl;
	cout << "\t ====== Current Folder Info ======" << endl;
	cout << "\t    folder name : " << folName << endl;
	cout << "\t    folder path : " << folPath << endl;
	cout << "\t    created time : " << folCreateTime << endl;
	cout << "\t    subfolder num : " << subFolNum << endl;
	cout << "\t    subfile num : " << subFilNum << endl;
	cout << "\t =================================" << endl << endl;
}

void FolderType::DisplaySubFolder() {
	std::cout << "\t ======== SubFolder list ========" << std::endl;
	if (subFolNum == 0) {
		std::cout << "\t ## NO FOLDER ##" << std::endl;
		std::cout << "\t ================================" << std::endl;
		return;
	}
	FolderType temp;
	subFolder->ResetList();
	for (int i = 0; i < subFolNum; ++i) {
		subFolder->GetNextItem(temp);
		std::cout << "\t    " << temp.GetName() << std::endl;
	}
	std::cout << "\t ================================" << std::endl;
}

void FolderType::DisplaySubFile() {
	std::cout << "\t ========= SubFile list =========" << std::endl;
	if (subFilNum == 0) {
		std::cout << "\t ## NO FILE ##" << std::endl;
		std::cout << "\t ================================" << std::endl;
		return;
	}
	FileType temp;
	subFile->ResetList();
	for (int i = 0; i < subFilNum; ++i) {
		subFile->GetNextItem(temp);
		std::cout << "\t    " << temp.GetName() << std::endl;
	}
	std::cout << "\t ================================" << std::endl;
}

FolderType* FolderType::GoToSubFolder() {
	FolderType sub, *ptr;
	sub.SetRecordFromKB();
	ptr = subFolder->GetPtr(sub);
	return ptr;
}

FileType* FolderType::OpenSubFile() {
	FileType sub, *ptr;
	sub.SetRecordFromKB();
	ptr = subFile->GetPtr(sub);
	return ptr;
}