#include "Application.h"

Application::Application() {
	root.setName("root");
	root.setPath("root");
	curFolder = &root;
	command = 'Q';
	clipBoard = nullptr;
	ItemType* rootPtr = &root;
	itemBoard.add(rootPtr);
}

Application::~Application() {
	if (clipBoard) {
		delete clipBoard;
		clipBoard = nullptr;
	}
}

void Application::run() {
	while (true) {
		system("color 2F");
		curFolder->displayInfo();
		command = getCommand();
		switch (command) {
		case 'A':
			addItem(1);
			break;
		case 'a':
			addItem(2);
			break;
		case 'D':
			deleteItem(1);
			break;
		case 'd':
			deleteItem(2);
			break;
		case 'R':
			try {
				goToRecentFolder();
			}
			catch (std::exception& ex) {
				std::cout << ex.what();
			}
			break;
		case 'r':
			try {
				runRecentFile();
			}
			catch (std::exception& ex) {
				std::cout << ex.what();
			}
			break;
		case 'O':
			try {
				openCurFolder();
			}
			catch (std::exception& ex) {
				std::cout << ex.what();
			}
			break;
		case 'o':
			try {
				runFile();
			}
			catch (std::exception& ex) {
				std::cout << ex.what();
			}
		case 'N':
			changeFolderName();
			break;
		case 'n':
			changeFileName();
			break;
		case 'S':
			try {
				retrieveFolder();
			}
			catch (std::exception& ex) {
				std::cout << ex.what();
			}
			break;
		case 's':
			try{
				retrieveFile();
			}
			catch (std::exception& ex) {
				std::cout << ex.what();
			}
			break;
		case 'C':
			try {
				copyItem(1);
			}
			catch (std::exception& ex) {
				std::cout << ex.what();
			}
			break;
		case 'c':
			try {
				copyItem(2);
			}
			catch (std::exception& ex) {
				std::cout << ex.what();
			}
			break;
		case 'P':
			pasteItem(1);
			break;
		case 'p':
			try {
				pasteItem(2);
			}
			catch (std::exception& ex) {
				std::cout << ex.what();
			}
			break;
		case 'B':
			try {
				moveBackward();
			}
			catch (std::exception& ex) {
				std::cout << ex.what();
			}
			break;
		case 'F':
			try {
				moveForward();
			}
			catch (std::exception& ex) {
				std::cout << ex.what();
			}
			break;
		case 'Q':
			return;
		default:
			std::cout << "\t ## Illegal selection... ##" << std::endl;
			break;
		}
	}
}

char Application::getCommand() {
	using namespace std;

	char selection;
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
	cin >> selection;
	return selection;
}

void Application::changeFolderName() {
	ItemType** temp;
	curFolder->displaySubfolder();
	if (curFolder->retrieveFolder(temp)) {
		std::string tempName;
		std::cout << "\t Enter folder name you want to change : ";
		std::cin >> tempName;
		(*temp)->setName(tempName);
		std::cout << "\t Change success!" << std::endl;
	}
}

void Application::changeFileName() {
	ItemType** temp;
	curFolder->displaySubfile();
	if (curFolder->retrieveFile(temp)) {
		std::string tempName;
		std::cout << "\t Enter file name you want to change : ";
		std::cin >> tempName;
		(*temp)->setName(tempName);
		std::cout << "\t Change success!" << std::endl;
	}
}

void Application::addItem(int operation) {
	if (operation == 1)
		curFolder->addItem(operation, itemBoard);
	else if (operation == 2)
		curFolder->addItem(operation, itemBoard);
}

void Application::deleteItem(int operation) {
	if (operation == 1)
		curFolder->deleteItem(operation, itemBoard);
	else if (operation == 2)
		curFolder->deleteItem(operation, itemBoard);
}

void Application::copyItem(int operation) {
	if (clipBoard) {
		delete clipBoard;
		clipBoard = nullptr;
	}
	if (operation == 1) {
		std::string tempName;
		curFolder->displaySubfolder();
		std::cout << "\t Enter file name you want to copy : ";
		std::cin >> tempName;
		curFolder->copyItem(operation, tempName, clipBoard);
	}
	else if (operation == 2) {
		std::string tempName;
		curFolder->displaySubfile();
		std::cout << "\t Enter file name you want to copy : ";
		std::cin >> tempName;
		curFolder->copyItem(operation, tempName, clipBoard);
	}
}

void Application::pasteItem(int operation) {
	if (!clipBoard) {
		std::cout << "\t ## No copy data ##" << std::endl;
		return;
	}
	if (operation == 1)
		curFolder->pasteItem(operation, clipBoard, itemBoard);
	else if (operation == 2)
		curFolder->pasteItem(operation, clipBoard, itemBoard);
}

void Application::moveBackward() {
	if (moveBack.isEmpty()) {
		std::cout << "\t ## No more back ##" << std::endl;
		return;
	}
	ItemType* temp1 = dynamic_cast<ItemType*>(curFolder), * temp2 = moveBack.getTop();
	moveBack.pop();
	moveFor.push(temp1);
	curFolder = dynamic_cast<FolderType*>(temp2);
	recentItem.enqueue(temp2);
}

void Application::moveForward() {
	if (moveFor.isEmpty()) {
		std::cout << "\t ## No more forward ##" << std::endl;
		return;
	}
	ItemType* temp1 = dynamic_cast<ItemType*>(curFolder), * temp2 = moveFor.getTop();
	moveFor.pop();
	moveBack.push(temp1);
	curFolder = dynamic_cast<FolderType*>(temp2);
	recentItem.enqueue(temp2);
}

void Application::openCurFolder() {
	using namespace std;

	int selection;
	cout << endl;
	cout << "\t ========= Folder Option =========" << endl;
	cout << "\t       1. Go to subfolder" << endl;
	cout << "\t       2. Go to parentfolder" << endl;
	cout << "\t =================================" << endl;
	while (true) {
		cout << "\t Choose : ";
		cin >> selection;
		if (selection == 1) {
			curFolder->displaySubfolder();
			goToSubFolder();
			break;
		}
		else if (selection == 2) {
			goToParFolder();
			break;
		}
		else cout << "\t ## INVALID SELECTION ##" << endl;
	}
}

void Application::runFile() {
	curFolder->displaySubfile();
	ItemType** temp;
	if (curFolder->retrieveFile(temp)) {
		FileType* open = dynamic_cast<FileType*>(*temp);
		open->run();
		recentItem.enqueue(*temp);
	}
	else
		std::cout << "\t ## Running Error ##" << std::endl;
}

void Application::goToSubFolder() {
	ItemType** open;
	if (curFolder->retrieveFolder(open)) {
		ItemType* temp = dynamic_cast<ItemType*>(curFolder);
		folderStack.push(temp);
		if (!moveFor.isEmpty()) moveFor.makeEmpty();
		moveBack.push(temp);
		recentItem.enqueue(*open);
		curFolder = dynamic_cast<FolderType*>(*open);
	}
	else
		std::cout << "\t ## Running Error ##" << std::endl;
}

void Application::goToParFolder() {
	if (folderStack.isEmpty()) {
		std::cout << "\t ## NO parents folder ##" << std::endl;
		return;
	}
	ItemType* temp = dynamic_cast<ItemType*>(curFolder), *open = folderStack.getTop();
	folderStack.pop();
	moveFor.makeEmpty();
	moveBack.push(temp);
	recentItem.enqueue(open);
	curFolder = dynamic_cast<FolderType*>(open);
}

void Application::goToRecentFolder() {
	std::cout << "\t ======= RecentFolder List =======" << std::endl;
	recentItem.print("folder");
	std::cout << "\t =================================" << std::endl;
	ItemType* temp, ** data = nullptr;
	std::string name;
	std::cout << "\t Enter the folder name you want to go(q is quit) : ";
	std::cin >> name;
	if (name == "q") return;
	temp = new FolderType;
	temp->setName(name);
	data = recentItem.getPtr(temp);
	if (data) {
		curFolder = dynamic_cast<FolderType*>(*data);
		if (!moveFor.isEmpty()) moveFor.makeEmpty();
		moveBack.push(*data);
		recentItem.enqueue(*data);
	}
	else
		std::cout << "\t ## ACCESS ERROR ##" << std::endl;
	delete temp;
}

void Application::runRecentFile() {
	std::cout << "\t ======== RecentFile List ========" << std::endl;
	recentItem.print("file");
	std::cout << "\t =================================" << std::endl;
	ItemType* temp, ** data = nullptr;
	std::string name;
	std::cout << "\t Enter the file name you want to run(q is quit) : ";
	std::cin >> name;
	if (name == "q") return;
	temp = new FileType;
	temp->setName(name);
	data = recentItem.getPtr(temp);
	if (data) {
		FileType* open = dynamic_cast<FileType*>(*data);
		open->run();
		recentItem.enqueue(*data);
	}
	else
		std::cout << "\t ## ACCESS ERROR ##" << std::endl;
	delete temp;
}

void Application::retrieveFolder() {
	if (itemBoard.getLength() == 1) {
		std::cout << "\t ## Already root ##" << std::endl;
		return;
	}
	ItemType* temp, ** data;
	std::string key;
	std::cout << "\t Enter the folder name you want to search : ";
	std::cin >> key;
	std::cout << "\t ======= Searching result =======" << std::endl;
	itemBoard.retrAndPrint("folder", key);
	std::cout << "\t ================================" << std::endl;
	key.clear();
	std::cout << "\t Enter the folder name you want to go(q is quit) : ";
	std::cin >> key;
	if (key == "q") return;
	temp = new FolderType;
	temp->setName(key);
	data = itemBoard.getPtr(temp);
	if (data) 
		curFolder = dynamic_cast<FolderType*>(*data);
	else
		std::cout << "\t ## ACCESS ERROR ##" << std::endl;
	delete temp;
}

void Application::retrieveFile() {
	if (itemBoard.getLength() == 1) {
		std::cout << "\t ## No data ##" << std::endl;
		return;
	}
	ItemType* temp, ** data;
	std::string key;
	std::cout << "\t Enter the file name you want to search : ";
	std::cin >> key;
	std::cout << "\t ======= Searching result =======" << std::endl;
	itemBoard.retrAndPrint("file", key);
	std::cout << "\t ================================" << std::endl;
	key.clear();
	std::cout << "\t Enter the file name you want to run(q is quit) : ";
	std::cin >> key;
	if (key == "q") return;
	temp = new FileType;
	temp->setName(key);
	data = itemBoard.getPtr(temp);
	if (data) {
		FileType* open = dynamic_cast<FileType*>(*data);
		open->run();
	}
	else
		std::cout << "\t ## ACCESS ERROR ##" << std::endl;
	delete temp;
}