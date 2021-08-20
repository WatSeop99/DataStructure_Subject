#include "Application.h"

Application::Application() {
	root.SetName("root");
	root.SetPath("root");
	curPtr = &root;
	m_Command = -1;
}

void Application::Run() {
	while (true) {
		std::cout << std::endl << "\t Current path : " << curPtr->GetPath() << std::endl;
		curPtr->DisplayFolderInfo();
		m_Command = GetCommand();
		switch (m_Command) {
		case 1:
			AddSubFolder();
			break;
		case 2:
			DeleteSubFolder();
			break;
		case 3:
			OpenFolder();
			break;
		case 4:
			RetrieveFolder();
			break;
		case 5:
			GetRecentFolder();
			break;
		case 6:
			MoveBackward();
			break;
		case 7:
			MoveForward();
			break;
		case 8:
			DisplayCurFolderInfo();
			break;
		case 0:
			return;
		default:
			std::cout << "\t ## Illegal selection... ##" << std::endl;
			break;
		}
	}
}

int Application::GetCommand() {
	using namespace std;

	int command;
	cout << endl;
	cout << "\t ================== Menu ==================" << endl;
	cout << "\t         1. Add new subfolder" << endl;
	cout << "\t         2. Delete subfolder" << endl;
	cout << "\t         3. Open folder" << endl;
	cout << "\t         4. Retrieve folder" << endl;
	cout << "\t         5. Display recent folder" << endl;
	cout << "\t         6. Move backward" << endl;
	cout << "\t         7. Move forward" << endl;
	cout << "\t         8. Display folder information" << endl;
	cout << "\t         0. Quit" << endl;
	cout << "\t ==========================================" << endl;
	cout << "\t Choose command->";
	cin >> command;
	return command;
}

void Application::OpenFolder() {
	int command;
	std::cout << std::endl;
	std::cout << "\t Choose the direction" << std::endl;
	std::cout << "\t  1. subfolder" << std::endl;
	std::cout << "\t  2. parentfolder" << std::endl;
	while (true) {
		std::cout << "\t Choose-> ";
		std::cin >> command;
		if (command == 1) {
			curPtr->DisplayFolderInfo();
			GoToSubFolder();
			break;
		}
		else if (command == 2) {
			GoToParFolder();
			break;
		}
		else std::cout << "\t ## Wrong choice ##" << std::endl;
	}
}

void Application::RetrieveFolder() {
	std::cout << "\t Please typing the name you want to search\n";
	curPtr->RetrieveFolderByName();
}

void Application::GetRecentFolder() {
	std::cout << "\t Open recent folder" << std::endl;
	std::cout << "\t ============= Recent Folder =============" << std::endl;
	recentFolder.Print();
	std::cout << "\t =========================================" << std::endl;
}

void Application::GoToSubFolder() {
	std::cout << "\t Please typing the name you want to go\n";
	folderStack.Push(curPtr);
	moveFoward.MakeEmpty();
	moveBack.Push(curPtr);
	curPtr = curPtr->GoToSubFolder();
	recentFolder.EnQueue(curPtr);
}

void Application::GoToParFolder() {
	if (folderStack.IsEmpty()) return;
	moveFoward.MakeEmpty();
	moveBack.Push(curPtr);
	curPtr = folderStack.Top();
	folderStack.Pop();
	recentFolder.EnQueue(curPtr);

}

void Application::MoveBackward() {
	if (folderStack.IsEmpty()) return;
	moveFoward.Push(curPtr);
	curPtr = moveBack.Top();
	moveBack.Pop();
	recentFolder.EnQueue(curPtr);
}

void Application::MoveForward() {
	if (moveFoward.IsEmpty()) return;
	moveBack.Push(curPtr);
	curPtr = moveFoward.Top();
	moveFoward.Pop();
	recentFolder.EnQueue(curPtr);
}