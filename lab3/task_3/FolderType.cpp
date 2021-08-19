#include "FolderType.h"

void FolderType::SetRecordFromKB() {
	std::string _name;
	std::cout << "\t Enter folder Name : ";
	std::cin >> _name;
	SetName(_name);
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
	if (data.SubFdList != nullptr)
		*SubFdList = *(data.SubFdList);
	return *this;
}

bool FolderType::AddSubFolder() {
	if (SubFdList == nullptr) SubFdList = new SortedList<FolderType>;
	FolderType subfol;
	subfol.SetRecordFromKB();
	subfol.SetPath(folPath + '\\' + subfol.folName);
	subfol.GenCreateTime();
	if (SubFdList->Add(subfol)) {
		std::cout << "\t Add success!" << std::endl;
		++SubFolderNum;
		return true;
	}
	else {
		std::cout << "\t Add fail!" << std::endl;
		return false;
	}
}

bool FolderType::DeleteSubFolder() {
	if (SubFdList == nullptr) {
		std::cout << "\t There is no list" << std::endl;
		return false;
	}
	FolderType temp;
	temp.SetRecordFromKB();
	if (SubFdList->Delete(temp)) {
		std::cout << "\t Delete success!" << std::endl;
		return true;
	}
	else {
		std::cout << "\t Delete fail!" << std::endl;
		return false;
	}
}

bool FolderType::RetrieveFolderByName() {
	if (SubFdList == nullptr) {
		std::cout << "\t There is no list" << std::endl;
		return false;
	}
	FolderType temp;
	temp.SetRecordFromKB();
	if (SubFdList->Get(temp) != -1) {
		temp.DisplayFolderInfo();
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
	cout << "\t =======Current Folder Info=======" << endl;
	cout << "\t    folder name : " << folName << endl;
	cout << "\t    folder path : " << folPath << endl;
	cout << "\t    created time : " << folCreateTime << endl;
	cout << "\t    subfolder num : " << SubFolderNum << endl;
	cout << "\t =================================" << endl << endl;
}

FolderType* FolderType::GoToSubFolder() {
	FolderType sub, *ptr;
	sub.SetRecordFromKB();
	SubFdList->ResetList();
	while (ptr = SubFdList->GetNextItemPtr())
		if (*ptr == sub) return ptr;
}