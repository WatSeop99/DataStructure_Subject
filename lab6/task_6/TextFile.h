#pragma once

#include <fstream>
#include "ContentsType.h"

class TextFile : public ContentsType {
public:
	void run(std::string _name);
	int getCommand();
	bool readText(std::string _name);
	bool writeText(std::string _name, int command);
private:
	std::ifstream inFile;
	std::ofstream outFile;
};