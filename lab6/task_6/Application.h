#pragma once

#include "FolderType.h"
#include "Stack.h"
#include "Queue.h"

class Application {
public:
	Application();
	~Application();

	void run();
	char getCommand();
	void changeFolderName();
	void changeFileName();
	void addItem(int operation);
	void deleteItem(int operation);
	void copyItem(int operation);
	void pasteItem(int operation);
	void moveBackward();
	void moveForward();
	void openCurFolder();
	void runFile();
	void goToSubFolder();
	void goToParFolder();
	void goToRecentFolder();
	void runRecentFile();
	void retrieveFolder();
	void retrieveFile();
private:
	FolderType root;
	FolderType* curFolder;
	LinkedList2<ItemType*> itemBoard;
	Stack<ItemType*> folderStack;
	Stack<ItemType*> moveBack;
	Stack<ItemType*> moveFor;
	Queue<ItemType*> recentItem;
	ItemType* clipBoard;
	char command;
};