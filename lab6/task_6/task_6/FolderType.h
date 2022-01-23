#pragma once

#include "ItemType.h"
#include "LinkedListForItem.h"
#include "FileType.h"

template <class Type>
class LinkedList;

class FileType;

class FolderType : public ItemType {
public:
	FolderType() : subList(nullptr), listNum(0) { type = "folder"; }
	FolderType(ItemType& data);
	~FolderType();

	int getListNum() const { return listNum; }
	ItemType& operator=(ItemType& data);
	bool addItem(int select, LinkedList2<ItemType*>& itemBoard);
	bool deleteItem(int select, LinkedList2<ItemType*>& itemBoard);
	bool copyItem(int select, std::string key, ItemType*& clipBoard);
	bool pasteItem(int select, ItemType*& clipBoard, LinkedList2<ItemType*>& itemBoard);
	bool retrieveFolder(ItemType**& data, std::string key);
	bool retrieveFile(ItemType**& data, std::string key);
	void displayInfo();
	void displaySubfolder();
	void displaySubfile();
private:
	LinkedList<ItemType*>* subList;
	int listNum;
};