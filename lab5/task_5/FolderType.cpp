#include "FolderType.h"

FolderType::FolderType() : folderName("\0"), folderPath("\0"), subFolder(nullptr), subFile(nullptr), 
	subFolderNum(0), subFileNum(0){
	GenCreateTime();
}

FolderType::FolderType(const FolderType& data) {
	folderName = data.folderName;
	folderPath = data.folderPath;
	folderCreateTime = data.folderCreateTime;
	subFolder = data.subFolder;
	subFile = data.subFile;
}

FolderType::~FolderType() {
	if (subFolder) delete subFolder;
	if (subFile) delete subFile;
}

void FolderType::SetRecordFromKB() {
	std::string name;
	std::cout << "\t Enter folder name : ";
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
	folderName = data.folderName;
	folderPath = data.folderPath;
	folderCreateTime = data.folderCreateTime;
	if (data.subFolderNum != 0) {
		subFolderNum = data.subFolderNum;
		subFolder = data.subFolder;
	}
	else {
		subFolderNum = 0;
		if (subFolder) subFolder->MakeEmpty();
	}
	if (data.subFileNum != 0) {
		subFileNum = data.subFileNum;
		subFile = data.subFile;
	}
	else {
		subFileNum = 0;
		if (subFile) subFile->MakeEmpty();
	}
	return *this;
}

std::ostream& operator<<(std::ostream& os, const FolderType& data) {
	os << data.folderName;
	return os;
}

bool FolderType::AddSubFolder() {
	if (!subFolder) subFolder = new LinkedList<FolderType>;
	FolderType subfol;
	subfol.SetRecordFromKB();
	subfol.SetPath(folderPath + '\\' + subfol.folderName);
	subfol.GenCreateTime();
	if (subFolder->Add(subfol)) {
		std::cout << "\t Add success!" << std::endl;
		++subFolderNum;
		return true;
	}
	else {
		std::cout << "\t Add fail!" << std::endl;
		return false;
	}
}

bool FolderType::AddSubFile() {
	if (!subFile) subFile = new LinkedList<FileType>;
	FileType subfil;
	subfil.SetRecordFromKB();
	subfil.SetPath(subfil.GetPath() + '\\' + subfil.GetName());
	if (subFile->Add(subfil)) {
		std::cout << "\t Add success!" << std::endl;
		++subFileNum;
		return true;
	}
	else {
		std::cout << "\t Add fail" << std::endl;
		return false;
	}
}

bool FolderType::DeleteSubFolder() {
	if (subFolderNum == 0) {
		std::cout << "\t ## NO SUBFOLDER ##" << std::endl;
		return false;
	}
	FolderType subfol;
	subfol.SetRecordFromKB();
	if (subFolder->Delete(subfol)) {
		std::cout << "\t Delete success!" << std::endl;
		--subFolderNum;
		return true;
	}
	else {
		std::cout << "\t Delete fail!" << std::endl;
		return false;
	}
}

bool FolderType::DeleteSubFile() {
	if (subFileNum == 0) {
		std::cout << "\t ## NO SUBFILE ##" << std::endl;
		return false;
	}
	FileType subfil;
	subfil.SetRecordFromKB();
	if (subFile->Delete(subfil)) {
		std::cout << "\t Delete success!" << std::endl;
		--subFileNum;
		return true;
	}
	else {
		std::cout << "\t Delete fail!" << std::endl;
		return false;
	}
}

bool FolderType::CopyFolder(FolderType*& data, std::string name) {
	FolderType temp;
	temp.SetName(name);
	if (data) {
		delete data;
		data = nullptr;
	}
	if (subFolderNum != 0 && subFolder->Get(temp)) {
		data = new FolderType;
		*data = temp;
		std::cout << "\t Copy folder success!" << std::endl;
		return true;
	}
	else {
		std::cout << "\t Copy folder fail!" << std::endl;
		return false;
	}
}

bool FolderType::CopyFile(FileType*& data, std::string name) {
	FileType temp;
	temp.SetName(name);
	if (data) {
		delete data;
		data = nullptr;
	}
	if (subFileNum != 0 && subFile->Get(temp)) {
		data = new FileType;
		*data = temp;
		std::cout << "\t Copy file success!" << std::endl;
		return true;
	}
	else {
		std::cout << "\t Copy file fail!" << std::endl;
		return false;
	}
}

bool FolderType::PasteFolder(FolderType*& data) {
	data->SetPath(folderPath + '\\' + folderName);
	if (!subFolder) subFolder = new LinkedList<FolderType>;
	if (subFolder->Add(*data)) {
		subFolderNum++;
		std::cout << "\t Paste folder success!" << std::endl;
		return true;
	}
	else {
		std::cout << "\t Paste folder fail!" << std::endl;
		return true;
	}
}

bool FolderType::PasteFile(FileType*& data) {
	data->SetPath(folderPath + '\\' + folderName);
	if (!subFile) subFile = new LinkedList<FileType>;
	if (subFile->Add(*data)) {
		subFileNum++;
		std::cout << "\t Paste file success!" << std::endl;
		return true;
	}
	else {
		std::cout << "\t Paste file fail!" << std::endl;
		return true;
	}
}

bool FolderType::RetrieveFolderByName(std::string key) {
	if (subFolderNum == 0) {
		std::cout << "\t ## NO SUBFOLDER ##" << std::endl;
		return false;
	}
	std::cout << "\t ========== Search List ==========" << std::endl;
	subFolder->RetrieveAndPrint(key);
	std::cout << "\t =================================" << std::endl;
}

bool FolderType::RetrieveFolderByName(FolderType*& data) {
	if (subFolderNum == 0) {
		std::cout << "\t ## NO SUBFOLDER ##" << std::endl;
		return false;
	}
	FolderType temp;
	std::string name;
	std::cout << "\t Enter folder name : ";
	std::cin >> name;
	data = subFolder->GetPtr(temp);
	if (data) {
		data->DisplayFolderInfo();
		return true;
	}
	else {
		std::cout << "\t ## NOT FOUND ##" << std::endl;
		return false;
	}
}

bool FolderType::RetrieveFileByName(std::string key) {
	if (subFileNum == 0) {
		std::cout << "\t ## NO SUBFILE ##" << std::endl;
		return false;
	}
	std::cout << "\t ========== Search List ==========" << std::endl;
	subFile->RetrieveAndPrint(key);
	std::cout << "\t =================================" << std::endl;
}

bool FolderType::RetrieveFileByName(FileType*& data) {
	if (subFileNum == 0) {
		std::cout << "\t ## NO SUBFILE ##" << std::endl;
		return false;
	}
	FileType temp;
	std::string name;
	std::cout << "\t Enter file name : ";
	std::cin >> name;
	data = subFile->GetPtr(temp);
	if (data) {
		data->DisplayFileInfo();
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
	cout << "\t    folder name : " << folderName << endl;
	cout << "\t    folder path : " << folderPath << endl;
	cout << "\t    created time : " << folderCreateTime << endl;
	cout << "\t    subfolder num : " << subFolderNum << endl;
	cout << "\t    subfile num : " << subFileNum << endl;
	cout << "\t =================================" << endl << endl;
}

void FolderType::DisplaySubFolder() {
	using namespace std;

	cout << endl;
	cout << "\t ======== Sub Folder List ========" << endl;
	if (subFolderNum == 0)
		cout << "\t    ## NO SUB FOLDER ## " << endl;
	else
		subFolder->Print();
	cout << "\t =================================" << endl << endl;
}

void FolderType::DisplaySubFile() {
	using namespace std;

	cout << endl;
	cout << "\t ========= Sub file List =========" << endl;
	if (subFileNum == 0)
		cout << "\t    ## NO SUB FILE ## " << endl;
	else
		subFile->Print();
	cout << "\t =================================" << endl << endl;
}

FolderType* FolderType::GoToSubFolder() {
	FolderType sub, * ptr;
	sub.SetRecordFromKB();
	ptr = subFolder->GetPtr(sub);
	return ptr;
}

FileType* FolderType::OpenSubFile() {
	FileType sub, * ptr;
	sub.SetRecordFromKB();
	ptr = subFile->GetPtr(sub);
	return ptr;
}