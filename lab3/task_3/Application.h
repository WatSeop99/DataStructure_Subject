#pragma once

#include "FolderType.h"
#include "Stack.h"
#include "Queue.h"

class Application {
private:
	FolderType root;
	FolderType* curPtr;
	Stack<FolderType*> folderStack;
	Stack<FolderType*> moveBack;
	Stack<FolderType*> moveFoward;
	Queue<FolderType*> recentFolder;
	int m_Command;
public:
	Application();
	~Application() { }

	void Run();
	int GetCommand();
	void AddSubFolder() { curPtr->AddSubFolder(); }
	void DeleteSubFolder() { curPtr->DeleteSubFolder(); }
	void OpenFolder();
	void RetrieveFolder();
	void GetRecentFolder();
	void GoToSubFolder();
	void GoToParFolder();
	void DisplayCurFolderInfo() const { curPtr->DisplayFolderInfo(); }
	void MoveBackward();
	void MoveForward();
};