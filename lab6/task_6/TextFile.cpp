#include "TextFile.h"

void TextFile::run(std::string _name) {
	std::cout << "\t  run..." << std::endl;
	int command;
	while (true) {
		command = getCommand();
		switch (command) {
		case 1:
			readText(name);
			break;
		case 2: case 3:
			WriteText(name, command);
			break;
		case 4:
			return;
		default:
			std::cout << "\t ## Illegal selection... ##" << std::endl;
			break;
		}
	}
}

int getCommend();
bool openFile(std::string _name);
bool writeFile(std::string _name, int command);