#pragma once

#include <fstream>
#include "ContentsType.h"

class TextFile : public ContentsType {
public:
	void run(std::string _name);
	int getCommend();
	bool openFile(std::string _name);
	bool writeFile(std::string _name, int command);
private:
	std::ifstream inFile;
	std::ofstream outFile;
};