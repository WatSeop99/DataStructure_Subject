#pragma once

#include "Folder.h"
#include "SystemConnect.h"
#include "Stack.h"
#include "Queue.h"

class Application
{
public:
	Application();
	~Application();

	bool AddItemFromWindow(const char* name, Item::eItemType type, void* param);
	bool ChangeFolNameFromWindow(const char* oldName, const char* newName);
	bool ChangeFilNameFromWindow(const char* oldName, const char* newName);
	bool DeleteItemFromWindow(const char* name, Item::eItemType type);
	Folder* GetCurFolder();
	bool OpencurFolderFromWindow(const char* name);
	File* RetrieveFileFromWindow(const char* name);
	Folder* RetrieveFolderFromWindow(const char* name);

private:
	Folder mRoot;
	Folder* mCurFolder;
};