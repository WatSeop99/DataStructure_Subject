#include "FolderType.h"

void FolderType::SetRecordFromKB() {
	std::string _name;
	std::cout << "\t Enter folder Name : ";
	std::cin >> _name;
	SetName(_name);
}

void FolderType::GenCreateTime() {
	using namespace std;

	time_t tt;
	struct tm*ti;
	time(&tt);
	ti = localtime(&tt);
	stringstream ss;
	ss << setw(4) << ti->tm_year + 1900 << setfill('0') << setw(2) << ti->tm_mon + 1 << setfill('0') << setw(2) << ti->tm_mday << setfill('0');
	ss << setw(2) << ti->tm_hour << setfill('0') << setw(2) << ti->tm_min << setfill('0') << setw(2) << ti->tm_sec << '\0';
	string ymd = ss.str();
	SetCreateTime(ymd);
}

FolderType& FolderType::operator=(const FolderType& data) {
	folName = data.folName;
	folPath = data.folPath;
	GenCreateTime();
	if (data.SubList != nullptr)
		*SubList = *(data.SubList);
	return *this;
}

bool FolderType::AddSubFolder() {
	if (SubList == nullptr) SubList = new SortedList;
	FolderType subfol;
	subfol.SetRecordFromKB();
	subfol.SetPath(folPath+'\\'+subfol.folName);
	subfol.GenCreateTime();
	if (SubList->Add(subfol)) {
		std::cout << "\t Add success!" << std::endl;
		++subFolNum;
		return true;
	}
	else {
		std::cout << "\t Add fail!" << std::endl;
		return false;
	}
}

bool FolderType::DeleteSubFolder() {
	FolderType temp;
	temp.SetRecordFromKB();
	if (SubList->Delete(temp)) {
		std::cout << "\t Delete success!" << std::endl;
		return true;
	}
	else {
		std::cout << "\t Delete fail!" << std::endl;
		return false;
	}
}

bool FolderType::RetrieveFolderByName() {
	FolderType temp;
	temp.SetRecordFromKB();
	if (SubList->Get(temp) != -1) {
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
	cout << "\t    created time : " << folCRTime << endl;
	cout << "\t    subfolder num : " << subFolNum << endl;
	cout << "\t =================================" << endl << endl;
}

FolderType* FolderType::GoToSubFolder() {
	FolderType sub, *ptr;
	sub.SetRecordFromKB();
	SubList->ResetList();
	while (ptr = SubList->GetNextItemPtr())
		if (*ptr == sub)
			return ptr;
}