#pragma once

#include "Stack.h"
#include "Queue.h"
#include "FolderType.h"

class Application {
private:
	FolderType root;
	FolderType* curFolder;
	FileType* curFile;
	Stack<FolderType*> folderStack;
	Stack<FolderType*> movdBack;
	Stack<FolderType*> moveForward;
	Queue<FolderType*> recentFolder;
	Queue<FileType*> recentFile;
	int m_Command;
public:
	Application();
	~Application();

	void Run();
	int GetCommand();
	void AddSubFolder() { curFolder->AddSubFolder(); }
	void DeleteSubFolder() { curFolder->DeleteSubFolder(); }
	void AddSubFile() { curFolder->AddSubFile(); }
	void DeleteSubFile() { curFolder->DeleteSubFile(); }
	void OpenFolder();
	void OpenFile();
	void RetrieveFolder();
	void RetrieveFile();
	void GetRecentFolder();
	void GetRecentFile();
	void GoToSubFolder();
	void GoToParFolder();
	void MoveBackward();
	void MoveForward();
	void DisplayCurFolderInfo() const { curFolder->DisplayFolderInfo(); }
	void DisplayCurFileInfo() const { curFile->DisplayFileInfo(); }
};