#include "Application.h"

Application::Application() {
	root.SetName("root");
	root.SetPath("root");
	curFolder = &root;
	curFile = nullptr;
	m_Command = 0;
}

void Application::Run() {
	while (true) {
		std::cout << std::endl << "\t Current path : " << curFolder->GetPath() << std::endl;
		curFolder->DisplaySubFolder();
		m_Command = GetCommand();
		switch (m_Command) {
		case 1:
			AddSubFolder();
			break;
		case 2:
			AddSubFile();
			break;
		case 3:
			DeleteSubFolder();
			break;
		case 4:
			DeleteSubFile();
			break;
		case 5:
			GetRecentFolder();
			break;
		case 6:
			GetRecentFile();
			break;
		case 7:
			MoveBackward();
			break;
		case 8:
			MoveForward();
			break;
		case 9:
			OpenFolder();
			break;
		case 10:
			OpenFile();
			break;
		case 11:
			RetrieveFolder();
			break;
		case 12:
			RetrieveFile();
			break;
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
	cout << "\t         1. Add subfolder" << endl;
	cout << "\t         2. Add subfile" << endl;
	cout << "\t         3. Delete subfolder" << endl;
	cout << "\t         4. Delete subfile" << endl;
	cout << "\t         5. Display recent folder" << endl;
	cout << "\t         6. Display recent file" << endl;
	cout << "\t         7. Move backward" << endl;
	cout << "\t         8. Move forward" << endl;
	cout << "\t         9. Open folder" << endl;
	cout << "\t        10. Open file" << endl;
	cout << "\t        11. Search subfolder" << endl;
	cout << "\t        12. Search subfile" << endl;
	cout << "\t ==========================================" << endl;
	cout << "\t Choose command->";
	cin >> command;
	return command;
}

void Application::OpenFolder() {
	using namespace std;

	int command;
	cout << endl;
	cout << "\t Choose the direction" << endl;
	cout << "\t 1. subfolder" << endl;
	cout << "\t 2. parentfolder" << endl;
	while (true) {
		cout << "\t Choose : ";
		cin >> command;
		if (command == 1) {
			curFolder->DisplaySubFolder();
			GoToSubFolder();
			break;
		}
		else if (command == 2) {
			GoToParFolder();
			break;
		}
		else cout << "\t ## Wrong choice ##" << endl;
	}
}

void Application::OpenFile() {
	std::cout << "\t Enter the file name that you want to open" << std::endl;
	curFile = curFolder->OpenSubFile();
	recentFile.EnQueue(curFile);
	curFile->DisplayFileInfo();
}

void Application::RetrieveFolder() {
	std::cout << "\t Please type the name you want to search\n";
	curFolder->RetrieveFolderByName();
}

void Application::RetrieveFile() {
	std::cout << "\t Please type the name you want to search\n";
	curFolder->RetrieveFileByName();
}

void Application::GetRecentFolder() {
	std::cout << "\t Open recent folder" << std::endl;
	std::cout << "\t ============= Recent Folder =============" << std::endl;
	recentFolder.Print();
	std::cout << "\t =========================================" << std::endl;
}

void Application::GetRecentFile() {
	std::cout << "\t Open recent file" << std::endl;
	std::cout << "\t ============== Recent File ==============" << std::endl;
	recentFile.Print();
	std::cout << "\t =========================================" << std::endl;
}

void Application::GoToSubFolder() {
	std::cout << "\t Please typing the name you want to go\n";
	folderStack.Push(curFolder);
	moveForward.MakeEmpty();
	moveBack.Push(curFolder);
	curFolder = curFolder->GoToSubFolder();
	recentFolder.EnQueue(curFolder);
}

void Application::GoToParFolder() {
	if (folderStack.IsEmpty()) return;
	moveForward.MakeEmpty();
	moveBack.Push(curFolder);
	curFolder = folderStack.Top();
	folderStack.Pop();
	recentFolder.EnQueue(curFolder);
}

void Application::MoveBackward() {
	if (folderStack.IsEmpty()) return;
	moveForward.Push(curFolder);
	curFolder = moveBack.Top();
	moveBack.Pop();
	recentFolder.EnQueue(curFolder);
}

void Application::MoveForward() {
	if (moveForward.IsEmpty()) return;
	moveBack.Push(curFolder);
	curFolder = moveForward.Top();
	moveForward.Pop();
	recentFolder.EnQueue(curFolder);
}