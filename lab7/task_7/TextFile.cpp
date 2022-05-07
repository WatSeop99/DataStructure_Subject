#include "TextFile.h"

void TextFile::run(std::string _name) {
	std::cout << "\t  run..." << std::endl;
	int command;
	while (true) {
		command = getCommand();
		switch (command) {
		case 1:
			readText(_name);
			break;
		case 2: case 3:
			writeText(_name, command);
			break;
		case 4:
			return;
		default:
			std::cout << "\t ## Illegal selection... ##" << std::endl;
			break;
		}
	}
}

int TextFile::getCommand() {
	using namespace std;

	int command;
	cout << endl;
	cout << "\t ========= Text File Menu =========" << endl;
	cout << "\t    1.  read text file" << endl;
	cout << "\t    2.  write new text file" << endl;
	cout << "\t    3.  write existing text file" << endl;
	cout << "\t    4.  quit" << endl;
	cout << "\t ==================================" << endl;
	cout << "\t Choose : ";
	cin >> command;
	return command;
}

bool TextFile::readText(std::string _name) {
	using namespace std;

	inFile.open(_name + ".txt");
	if (!inFile) return false;
	cout << endl;
	cout << "\t =========== Text File ===========" << endl;
	string line;
	while (getline(inFile, line))
		cout << "\t     " << line << endl;
	cout << "\t =================================" << endl;
	cout << endl;
	inFile.close();
	return true;
}

bool TextFile::writeText(std::string _name, int command) {
	using namespace std;

	if (command == 2) {
		outFile.open(_name + ".txt");
		cout << endl;
		cout << "\t ========= Type the text =========" << endl;
		cout << "\t     input ('q' is quit) : ";
		string line;
		while (getline(cin, line)) {
			if (line == "q") break;
			outFile << line << '\n';
			cout << "\t     ";
		}
	}
	else if (command == 3) {
		outFile.open(_name + ".txt", ios::app);
		if (!outFile) return false;
		cout << "\t ========= Type the text =========" << endl;
		cout << "\t     input ('q' is quit) : ";
		string line;
		while (getline(cin, line)) {
			if (line == "q") break;
			outFile << line << '\n';
			cout << "\t     ";
		}
	}
	outFile.close();
	return true;
}