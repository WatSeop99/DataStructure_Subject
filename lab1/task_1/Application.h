#pragma once

#include "ArrayList.h"

#define FILENAMESIZE 1024

class Application {
private:
	std::ifstream m_InFile;
	std::ofstream m_OutFile;
	ArrayList m_List;
	int m_Command;
public:
	Application() { m_Command = -1; }
	~Application() { }

	void Run();
	int GetCommand();
	bool AddItem();
	void DisAplayAllItem();
	bool OpenInFile(char* fileName);
	bool OpenOutFile(char* fileName);
	bool ReadDataFromFile();
	bool WriteDataToFile();
	bool DeleteItem();
	bool ReplaceItem();
	void DisplayItem();
	bool MakeEmptyList();
};