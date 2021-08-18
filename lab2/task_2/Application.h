#pragma once

#include <fstream>
#include "FolderType.h"

class Application {
private:
	FolderType root;
	FolderType *curPtr, *parPtr;
	std::ifstream m_inFile;
	std::ofstream m_OutFile;
	int m_Command;
public:
	Application() {
		root.SetName("root");
		root.SetPath("root");
		curPtr = &root, parPtr = nullptr;
		m_Command = -1;
	}
	~Application() { }

	void Run();
	int GetCommand();
	void AddFol();
	void DeleteFol();
	void GoToSubFol();
	void GoToParFol() { curPtr = parPtr; }
	void RetrieveFolderByName() { curPtr->RetrieveFolderByName(); }
	void DisplayProperty() { curPtr->DisplayFolderInfo(); }
};