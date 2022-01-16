#pragma once

#include "Stack.h"
#include "Queue.h"
#include "FolderType.h"
using namespace std;

class Application {
private:
	FolderType root;
	FolderType* curFolder;
	FileType* curFile;
	Stack<FolderType*> folderStack;
	Stack<FolderType*> moveBack;
	Stack<FolderType*> moveFor;
	Queue<FolderType*> recentFolder;
	Queue<FileType*> recentFile;
	FolderType* clipFolder;
	FileType* clipFile;
	char m_Command;
public:
	Application();
	~Application();

	void Run();
	char GetCommand();
	void ChangeFolderName();
	void ChangeFileName();
	void AddSubFolder() { curFolder->AddSubFolder(); }
	void DeleteSubFolder() { curFolder->DeleteSubFolder(); }
	void AddSubFile() { curFolder->AddSubFile(); }
	void DeleteSubFile() { curFolder->DeleteSubFile(); }
	void CopySubFolder();
	void CopySubFile();
	void PasteSubFolder();
	void PasteSubFile();
	void OpenFolder();
	void OpenFile();
	void RetrieveFolder();
	void RetrieveFile();
	void GoToRecentFolder();
	void RunRecentFile();
	void GoToSubFolder();
	void GoToParFolder();
	void MoveBackward();
	void MoveForward();
	void DisplayCurFolderInfo() const { curFolder->DisplayFolderInfo(); }
	void DisplayCurFileInfo() const { curFile->DisplayFileInfo(); }
};