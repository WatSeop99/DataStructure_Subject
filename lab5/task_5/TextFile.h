#pragma once

#include <fstream>
#include "ItemType.h"

class TextFile : public ItemType {
private:
	std::ifstream inFile;
	std::ofstream outFile;
public:
	TextFile() { }
	~TextFile() { }

	void Run(std::string name);
	int GetCommand();
	bool ReadText(std::string name);
	bool WriteText(std::string name, int command);
};