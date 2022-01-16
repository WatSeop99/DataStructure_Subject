#include "Application.h"

Application::Application() {
	root.SetName("root");
	root.SetPath("root");
	curFolder = &root;
	curFile = nullptr;
	m_Command = 0;
}

Application::~Application() {
	if (clipFolder) delete clipFolder;
	if (clipFile) delete clipFile;
}

void Application::Run() {
	while (true) {
		system("color 2F");
		std::cout << std::endl << "\t Current path : " << curFolder->GetPath() << std::endl;
		curFolder->DisplaySubFolder();
		m_Command = GetCommand();
		switch (m_Command) {
		case 'A':
			AddSubFolder();
			break;
		case 'a':
			AddSubFile();
			break;
		case 'D':
			DeleteSubFolder();
			break;
		case 'd':
			DeleteSubFile();
			break;
		case 'R':
			try {
				GoToRecentFolder();
			}
			catch (exception& ex) {
				std::cout << ex.what();
			}
			break;
		case 'r':
			try {
				RunRecentFile();
			}
			catch (exception& ex) {
				std::cout << ex.what();
			}
			break;
		case 'B':
			try {
				MoveBackward();
			}
			catch (exception& ex) {
				std::cout << ex.what();
			}
			break;
		case 'b':
			try {
				MoveForward();
			}
			catch (exception& ex) {
				std::cout << ex.what();
			}
			break;
		case 'O':
			try {
				OpenFolder();
			}
			catch (exception& ex) {
				std::cout << ex.what();
			}
			break;
		case 'o':
			try {
				OpenFile();
			}
			catch (exception& ex) {
				std::cout << ex.what();
			}
			break;
		case 'N':
			ChangeFolderName();
			break;
		case 'n':
			ChangeFileName();
			break;
		case 'S':
			try {
				RetrieveFolder();
			}
			catch (exception& ex) {
				cout << ex.what();
			}
			break;
		case 's':
			try {
				RetrieveFile();
			}
			catch (exception& ex) {
				cout << ex.what();
			}
			break;
		case 'C':
			CopySubFolder();
			break;
		case 'c':
			CopySubFile();
			break;
		case 'P':
			PasteSubFolder();
			break;
		case 'p':
			PasteSubFile();
			break;
		case 'Q':
			return;
		default:
			std::cout << "\t ## Illegal selection... ##" << std::endl;
			break;
		}
	}
}

char Application::GetCommand() {
	using namespace std;

	char command;
	cout << endl;
	cout << "\t ========================= Menu =========================" << endl;
	cout << "\t      folder func            |       file func" << endl;
	cout << "\t  * add subfolder(A)         |  * add subfile(a)" << endl;
	cout << "\t  * delete subfolder(D)      |  * delete subfile(d)" << endl;
	cout << "\t  * open recent folder(R)    |  * open recent file(r)" << endl;
	cout << "\t  * open subfolder(O)        |  * open subfile(o)" << endl;
	cout << "\t  * change subfolder name(N) |  * change subfile name(n)" << endl;
	cout << "\t  * retrieve subfolder(S)    |  * retrieve subfile(s)" << endl;
	cout << "\t  * copy folder(C)           |  * copy file(c)" << endl;
	cout << "\t  * paste folder(P)          |  * paste file(p)" << endl;
	cout << "\t --------------------------------------------------------" << endl;
	cout << "\t                           Others" << endl;
	cout << "\t                   * move backward(B)" << endl;
	cout << "\t                   * move forward(F)" << endl;
	cout << "\t                   * quit(Q)" << endl;
	cout << "\t ========================================================" << endl;
	cout << "\t Choose command->";
	cin >> command;
	return command;
}

void Application::ChangeFolderName() {
	FolderType* temp;
	if (curFolder->RetrieveFolderByName(temp)) {
		std::string name;
		std::cout << "\t Enter folder name you want to change : ";
		std::cin >> name;
		temp->SetName(name);
	}
}

void Application::ChangeFileName() {
	FileType* temp;
	if (curFolder->RetrieveFileByName(temp)) {
		std::string name;
		std::cout << "\t Enter file name you want to change : ";
		std::cin >> name;
		temp->SetName(name);
	}
}

void Application::CopySubFolder() {
	std::string name;
	curFolder->DisplaySubFolder();
	std::cout << "\t Enter folder name you want to copy : ";
	std::cin >> name;
	curFolder->CopyFolder(clipFolder, name);
}

void Application::CopySubFile() {
	std::string name;
	curFolder->DisplaySubFile();
	std::cout << "\t Enter file name you want to copy : ";
	std::cin >> name;
	curFolder->CopyFile(clipFile, name);
}

void Application::PasteSubFolder() {
	if (!clipFolder)
		std::cout << "\t ## No copy data ##" << std::endl;
	curFolder->PasteFolder(clipFolder);
}

void Application::PasteSubFile() {
	if (!clipFile)
		std::cout << "\t ## No copy data ## " << std::endl;
	curFolder->PasteFile(clipFile);
}

void Application::OpenFolder() {
	using namespace std;

	int command;
	cout << endl;
	cout << "\t ========= Folder Option =========" << endl;
	cout << "\t       1. Go to subfolder" << endl;
	cout << "\t       2. Go to parentfolder" << endl;
	cout << "\t =================================" << endl;
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
		else cout << "\t ## INVALID SELECTION ##" << endl;
	}
}

void Application::OpenFile() {
	curFolder->DisplaySubFile();
	FileType* temp;
	if (curFolder->RetrieveFileByName(temp)) {
		temp->OpenFile();
		recentFile.EnQueue(temp);
	}
}

void Application::RetrieveFolder() {
	std::string key;
	std::cout << "\t Enter the folder keyword : ";
	std::cin >> key;
	curFolder->RetrieveFolderByName(key);
}

void Application::RetrieveFile() {
	std::string key;
	std::cout << "\t Enter the file keyword : ";
	std::cin >> key;
	curFolder->RetrieveFileByName(key);
}

void Application::GoToRecentFolder() {
	std::cout << "\t ======= RecentFolder List =======" << std::endl;
	recentFolder.Print();
	std::cout << "\t =================================" << std::endl;
	FolderType* temp, * data;
	std::string name;
	std::cout << "\t Enter the folder name you want to go(q is quit) : ";
	std::cin >> name;
	if (name == "q") return;
	data = new FolderType;
	data->SetName(name);
	recentFolder.Get(temp, data);
	if (temp) {
		curFolder = temp;
		if (!moveFor.IsEmpty()) moveFor.MakeEmpty();
		moveBack.Push(curFolder);
		recentFolder.EnQueue(curFolder);
	}
	else
		cout << "\t ## ACCESS ERROR ##" << endl;
	delete data;
}

void Application::RunRecentFile() {
	std::cout << "\t ======== RecentFile List ========" << std::endl;
	recentFile.Print();
	std::cout << "\t =================================" << std::endl;
	FileType* temp, * data;
	std::string name;
	std::cout << "\t Enter the file name you want to run(q is quit) : ";
	std::cin >> name;
	if (name == "q") return;
	data = new FileType;
	data->SetName(name);
	recentFile.Get(temp, data);
	if (temp) {
		temp->OpenFile();
		recentFile.EnQueue(temp);
	}
	else cout << "\t ## ACCESS ERROR ##" << endl;
	delete data;
}

void Application::GoToSubFolder() {
	std::cout << "\t Please type the name you want to go\n";
	folderStack.Push(curFolder);
	moveFor.MakeEmpty();
	moveBack.Push(curFolder);
	curFolder = curFolder->GoToSubFolder();
	recentFolder.EnQueue(curFolder);
}

void Application::GoToParFolder() {
	if (folderStack.IsEmpty()) return;
	moveFor.MakeEmpty();
	moveBack.Push(curFolder);
	curFolder = folderStack.Top();
	folderStack.Pop();
	recentFolder.EnQueue(curFolder);
}

void Application::MoveBackward() {
	if (folderStack.IsEmpty()) return;
	moveFor.Push(curFolder);
	curFolder = moveBack.Top();
	moveBack.Pop();
	recentFolder.EnQueue(curFolder);
}

void Application::MoveForward() {
	if (moveFor.IsEmpty()) return;
	moveBack.Push(curFolder);
	curFolder = moveFor.Top();
	moveFor.Pop();
	recentFolder.EnQueue(curFolder);
}