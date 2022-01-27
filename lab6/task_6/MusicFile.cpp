#include "MusicFile.h"

void MusicFile::setRecord() {
	std::string input;
	std::cout << "\t Enter the title : ";
	std::cin >> input;
	title = input;
	input.clear();
	std::cout << "\t Enter the artist : ";
	std::cin >> input;
	artist = input;
	input.clear();
	std::cout << "\t Enter the album : ";
	std::cin >> input;
	album = input;
}

void MusicFile::run(std::string _name) {
	int command;
	while (true) {
		command = getCommand();
		switch (command) {
		case 1:
			displayMusicInfo();
			break;
		case 2:
			return;
		default:
			std::cout << "\t ## INVALID SELECTION ##" << std::endl;
			break;
		}
	}
}

int MusicFile::getCommand() {
	using namespace std;

	int command;
	cout << endl;
	cout << "\t ========= Music File Menu =========" << endl;
	cout << "\t    1.  open music file info" << endl;
	cout << "\t    2.  quit" << endl;
	cout << "\t ===================================" << endl;
	cout << "\t Choose : ";
	cin >> command;
	return command;
}
void MusicFile::displayMusicInfo() {
	using namespace std;

	cout << endl;
	cout << "\t ========= Music File Info =========" << endl;
	cout << "\t    title : " << title << endl;
	cout << "\t    artist : " << artist << endl;
	cout << "\t    album : " << album << endl;
	cout << "\t ===================================" << endl;
}