#include "FolderType.h"

FolderType::FolderType(ItemType& data) {
	FolderType* tempPtr = dynamic_cast<FolderType*> (&data);
	name = tempPtr->name;
	path = tempPtr->path;
	createTime = tempPtr->createTime;
	type = "folder";
	if (tempPtr->listNum) {
		subList = new BinarySearchTree<ItemType*>;
		*subList = *tempPtr->subList;
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
		subList = new BinarySearchTree<ItemType*>;
		*subList = *(tempPtr->subList);
		listNum = tempPtr->listNum;
	}
	else {
		subList = nullptr;
		listNum = 0;
	}
	return *this;
}

bool FolderType::addItem(int select) {
	if (!subList) subList = new BinarySearchTree<ItemType*>;
	// select : 1 > add folder, 2 > add file
	bool success = false;
	if (select == 1) {
		ItemType* newFolder = new FolderType;
		newFolder->setRecordFromKB();
		newFolder->setPath(path + '\\' + newFolder->getName());
		if (subList->addData(newFolder)) {
			++listNum;
			success = true;
		}
	}
	else if (select == 2) {
		ItemType* newFile = new FileType;
		std::string type;
		newFile->setRecordFromKB();
		newFile->setPath(path + '\\' + newFile->getName());
		std::cout << "\t Enter the type you want(text, image, music) : ";
		std::cin >> type;
		newFile->setType(type);
		if (subList->addData(newFile)) {
			++listNum;
			success = true;
		}
	}
	if (success) std::cout << "\t Add success!" << std::endl;
	else std::cout << "\t Add fail!" << std::endl;
	return success;
}

bool FolderType::deleteItem(int select) {
	if (listNum == 0) {
		std::cout << "\t ## NO SUBFOLDER ##" << std::endl;
		return false;
	}
	// select : 1 > delete folder, 2 > delete file
	bool success = false;
	if (select == 1) {
		ItemType* delFolder = new FolderType;
		delFolder->setRecordFromKB();
		if (subList->removeData(delFolder)) {
			--listNum;
			success = true;
		}
	}
	else if (select == 2) {
		ItemType* delFile = new FileType;
		delFile->setRecordFromKB();
		if (subList->removeData(delFile)) {
			--listNum;
			success = true;
		}
	}
	if (success) std::cout << "\t Delete success!" << std::endl;
	else std::cout << "\t Delete fail!" << std::endl;
	return success;
}

bool FolderType::copyItem(int select, std::string key, ItemType*& clipBoard) {

}

bool FolderType::pasteItem(int select, ItemType*& clipBoard) {

}

bool FolderType::retrieveFolder(ItemType**& data) {

}

bool FolderType::retrieveFile(ItemType**& data) {

}

void FolderType::displayInfo() {

}

void FolderType::displaySubfolder() {

}

void FolderType::displaySubfile() {

}