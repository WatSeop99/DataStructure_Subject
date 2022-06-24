#pragma once

#include "BinarySearchTree.h"
#include "File.h"
#include "Item.h"
#include "SystemConnect.h"

class File;

class Folder : public Item
{
public:
	Folder();
	Folder(Item& data);
	~Folder();

	bool Add(Item& data, Item::eItemType type);
	bool Copy(Item* outData, std::string name, Item::eItemType type) const;
	bool Delete(Item& data, Item::eItemType type);
	int GetLength() const;
	void PathUpdate(Folder* folder, std::string path);
	bool Paste(Item& data, Item::eItemType select);
	bool RetrieveAll(Item* outData, Item& comp);
	bool RetrieveFile(Item* outData, std::string name);
	bool RetrieveFolder(Item* outData, std::string name);

	Item& operator=(Item& data);

private:
	BinarySearchTree<Item*>* mList;
};