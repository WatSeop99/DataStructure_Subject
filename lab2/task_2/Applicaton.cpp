#include "Application.h"

void Application::Run() {
	while (true) {
		m_Command = GetCommand();
		switch (m_Command) {
		case 1:
			AddFol();
			break;
		case 2:
			RetrieveFolderByName();
			break;
		case 3:
			DeleteFol();
			break;
		case 4:
			DisplayProperty();
			break;
		case 5:
			GoToSubFol();
			break;
		case 6:
			GoToParFol();
			break;
		case 0:
			return;
		default:
			std::cout << "\tIllegal selection...\n";
			break;
		}
	}
}

int Application::GetCommand() {
	using namespace std;

	int command;
	cout << endl << endl;
	cout << "\t ============ Main Page ===========" << endl;
	cout << "\t   [ " << curPtr->GetName() << " ]" << endl;
	cout << "\t   1 : Add subfolder" << endl;
	cout << "\t   2 : Search the subfolder" << endl;
	cout << "\t   3 : Delete subfolder" << endl;
	cout << "\t   4 : Display current folder property" << endl;
	cout << "\t   5 : Go to subfolder" << endl;
	cout << "\t   6 : Go to parentfolder" << endl;
	cout << "\t   0 : Quit" << endl;
	cout << "\t ==================================" << endl;
	cout << endl << "\t Choose a Command--> ";
	cin >> command;
	cout << endl;
	return command;
}

void Application::AddFol() {
	std::cout << "\t Adding SubFolder!!\n";
	curPtr->AddSubFolder();
}

void Application::DeleteFol() {
	std::cout << "\t Deleting SubFolder!!\n";
	curPtr->DeleteSubFolder();
}

void Application::GoToSubFol() {
	std::cout << "\t Please typing the name you want to go\n";
	parPtr = curPtr;
	curPtr = curPtr->GoToSubFolder();
}