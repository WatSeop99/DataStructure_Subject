#include "Application.h"

void Application::Run() {
	while (true) {
		m_Command = GetCommand();
		switch (m_Command) {
		case 1:
			AddItem();
			DisAplayAllItem();
			break;
		case 2:
			DeleteItem();
			break;
		case 3:
			ReplaceItem();
			break;
		case 4:
			DisplayItem();
			break;
		case 5:
			DisAplayAllItem();
			break;
		case 6:
			MakeEmptyList();
			break;
		case 7:
			ReadDataFromFile();
			DisAplayAllItem();
			break;
		case 8:
			WriteDataToFile();
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
	cout << "\t---ID -- Command ----- " << endl;
	cout << "\t   1 : Add item" << endl;
	cout << "\t   2 : Delete item" << endl;
	cout << "\t   3 : Replace item" << endl;
	cout << "\t   4 : Print item on screen" << endl;
	cout << "\t   5 : Print all on screen" << endl;
	cout << "\t   6 : Delete all" << endl;
	cout << "\t   7 : Get from file" << endl;
	cout << "\t   8 : Put to file" << endl;
	cout << "\t   0 : Quit" << endl;
	cout << endl << "\t Choose a Command--> ";
	cin >> command;
	cout << endl;
	return command;
}

bool Application::AddItem() {
	ItemType input;
	input.SetRecordFromKB();
	if (m_List.Add(input))
		return true;
	else {
		std::cout << "\n\t###Add error###" << std::endl;
		return false;
	}
}

void Application::DisAplayAllItem() {
	ItemType data;
	std::cout << "\n\tCurrent list" << std::endl;
	m_List.ResetList();
	while (m_List.GetNextItem(data) != -1) {
		data.DisplayRecordOnScreen();
		std::cout << std::endl;
	}
}

bool Application::OpenInFile(char* fileName) {
	m_InFile.open(fileName);
	return m_InFile.is_open() ? true : false;
}

bool Application::OpenOutFile(char* fileName) {
	m_OutFile.open(fileName);
	return m_OutFile.is_open() ? true : false;
}

bool Application::ReadDataFromFile() {
	int idx = 0;
	ItemType data;
	char fileName[FILENAMESIZE];
	std::cout << "\n\tEnter Input file Name : ";
	std::cin >> fileName;
	if (!OpenInFile(fileName))
		return false;
	m_List.MakeEmpty();
	while (data.ReadDataFromFile(m_InFile))
		m_List.Add(data);
	m_InFile.close();
	return true;
}

bool Application::WriteDataToFile() {
	ItemType data;
	char fileName[FILENAMESIZE];
	std::cout << "\n\tEnter Input file Name : ";
	std::cin >> fileName;
	if (!OpenOutFile(fileName))
		return false;
	m_List.ResetList();
	while (m_List.GetNextItem(data) != -1)
		data.WriteDataToFile(m_OutFile);
	m_OutFile.close();
	return true;
}

bool Application::DeleteItem() {
	ItemType output;
	std::cout << "\n\tEnter Id to delete" << std::endl;
	output.SetIdFromKB();
	if (m_List.Delete(output))
		return true;
	else {
		std::cout << "\n\t###Delete error###" << std::endl;
		return false;
	}
}

bool Application::ReplaceItem() {
	ItemType data;
	std::cout << "\n\tEnter Record to replace" << std::endl;
	data.SetRecordFromKB();
	if (m_List.RePlace(data))
		return true;
	else {
		std::cout << "\n\t###Replace error###" << std::endl;
		return 0;
	}
}

void Application::DisplayItem() {
	ItemType data;
	std::cout << "\n\tEnter Record to display" << std::endl;
	data.SetIdFromKB();
	if (m_List.Get(data)) {
		std::cout << std::endl << "\n\tItem" << std::endl;
		data.DisplayRecordOnScreen();
	}
	else
		std::cout << "\n\tItem Not Found" << std::endl;
}

bool Application::MakeEmptyList() {
	m_List.MakeEmpty();
	return true;
}