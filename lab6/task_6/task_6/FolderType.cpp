#include "FolderType.h"

FolderType::FolderType(ItemType& data) {
	FolderType* tempPtr = dynamic_cast<FolderType*> (&data);
	name = tempPtr->name;
	path = tempPtr->path;
	createTime = tempPtr->createTime;
	type = "folder";
	if (tempPtr->listNum) {
		subList = new LinkedList<ItemType*>;
		*subList = *(tempPtr->subList);
		listNum = tempPtr->listNum;
	}
	else {
		subList = nullptr;
		listNum = 0;
	}
}

FolderType::~FolderType() {
	if (subList) {
		delete subList;
		subList = nullptr;
	}
}

ItemType& FolderType::operator=(ItemType& data) {
	FolderType* tempPtr = dynamic_cast<FolderType*> (&data);
	name = tempPtr->name;
	path = tempPtr->path;
	createTime = tempPtr->createTime;
	type = "folder";
	if (tempPtr->listNum) {
		if (subList) delete subList;
		subList = new LinkedList<ItemType*>;
		*subList = *(tempPtr->subList);
		listNum = tempPtr->listNum;
	}
	else {
		subList = nullptr;
		listNum = 0;
	}
	return *this;
}

bool FolderType::addItem(int select, LinkedList2<ItemType*>& itemBoard) {
	if (!subList) subList = new LinkedList<ItemType*>;
	// select : 1 > add folder, 2 > add file
	bool success = false;
	if (select == 1) {
		ItemType* newFolder = new FolderType;
		newFolder->setRecordFromKB();
		newFolder->setPath(path + '\\' + newFolder->getName());
		if (subList->add(newFolder)) {
			++listNum;
			success = true;
		}
	}
	else if (select == 2) {
		ItemType* newFile = new FileType;
		newFile->setRecordFromKB();
		newFile->setPath(path + '\\' + newFile->getName());
		if (subList->add(newFile)) {
			++listNum;
			success = true;
		}
	}
	if (success) std::cout << "\t Add success!" << std::endl;
	else std::cout << "\t Add fail!" << std::endl;
	return success;
}

bool FolderType::deleteItem(int select, LinkedList2<ItemType*>& itemBoard) {
	if (listNum == 0) {
		std::cout << "\t ## NO SUBFOLDER ##" << std::endl;
		return false;
	}
	// select : 1 > delete folder, 2 > delete file
	bool success = false;
	if (select == 1) {
		ItemType* delFolder = new FolderType;
		delFolder->setRecordFromKB();
		if (subList->remove(delFolder)) {
			--listNum;
			success = true;
		}
	}
	else if (select == 2) {
		ItemType* delFile = new FileType;
		delFile->setRecordFromKB();
		if (subList->remove(delFile)) {
			--listNum;
			success = true;
		}
	}
	if (success) std::cout << "\t Delete success!" << std::endl;
	else std::cout << "\t Delete fail!" << std::endl;
	return success;
}

bool FolderType::copyItem(int select, std::string key, ItemType*& clipBoard) {
	if (clipBoard) {
		delete clipBoard;
		clipBoard = nullptr;
	}
	// select : 1 > copy folder, 2 > copy file
	bool success = false;
	if (select == 1) {
		ItemType* temp = new FolderType;
		temp->setName(key);
		if (listNum && subList->get(temp)) {
			clipBoard = new FolderType;
			*clipBoard = *temp;
			delete temp;
			success = true;
		}
	}
	else if (select == 2) {
		ItemType* temp = new FileType;
		temp->setName(key);
		if (listNum && subList->get(temp)) {
			clipBoard = new FileType;
			*clipBoard = *temp;
			delete temp;
			success = true;
		}
	}
	if (success) std::cout << "\t Copy success!" << std::endl;
	else std::cout << "\t Copy fail!" << std::endl;
	return success;
}

bool FolderType::pasteItem(int select, ItemType*& clipBoard, LinkedList2<ItemType*>& itemBoard) {
	if (!subList) subList = new LinkedList<ItemType*>;
	// select : 1 > copy folder, 2 > copy file
	bool success = false;
	if (select == 1 && clipBoard->getType().compare("folder") == 0) {

	}
}

bool FolderType::retrieveFolder(ItemType**& data, std::string key);
bool FolderType::retrieveFile(ItemType**& data, std::string key);
void FolderType::displayInfo();
void FolderType::displaySubfolder();
void FolderType::displaySubfile();