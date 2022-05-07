#pragma once

#include "FileType.h"
#include "BinarySearchTree.h"

class FileType;

template <class Type>
class BinarySearchTree;

class FolderType : public ItemType {
public:
	FolderType() : subList(nullptr), listNum(0) { type = "folder"; }
	FolderType(ItemType& data);
	~FolderType();

	int getListNum() const { return listNum; }
	ItemType& operator=(ItemType& data);
	bool addItem(int select);
	bool deleteItem(int select);
	bool copyItem(int select, std::string key, ItemType*& clipBoard);
	bool pasteItem(int select, ItemType*& clipBoard);
	bool retrieveFolder(ItemType**& data);
	bool retrieveFile(ItemType**& data);
	void displayInfo();
	void displaySubfolder();
	void displaySubfile();
private:
	BinarySearchTree<ItemType*>* subList;
	int listNum;
};