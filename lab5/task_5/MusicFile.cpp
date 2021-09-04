#include "MusicFile.h"

void MusicFile::SetRecord() {
	std::string input;
	std::cout << "\t  ���� ���� �Է� : ";
	std::cin >> input;
	SetTitle(input);
	input.clear();
	std::cout << "\t  ��Ƽ��Ʈ �Է� : ";
	std::cin >> input;
	SetArtist(input);
	input.clear();
	std::cout << "\t  �ٹ� �Է� : ";
	std::cin >> input;
	SetAlbum(input);
	input.clear();
}

void MusicFile::Run(std::string name) {
	int command;
	while (true) {
		command = GetCommand();
		switch (command) {
		case 1:
			DisplayMusicInfo();
			break;
		case 2:
			return;
		default:
			std::cout << "\t ## Illegal selection... ##" << std::endl;
			break;
		}
	}
}

int MusicFile::GetCommand() {
	using namespace std;

	int command;
	cout << endl;
	cout << "\t  ==========================" << endl;
	cout << "\t  || Music ���� �۾� �޴� ||" << endl;
	cout << "\t  ===========================================================================" << endl;
	cout << "\t     1.  Music ���� ���� ���" << endl;
	cout << "\t     2.  Music ���� ����" << endl;
	cout << "\t  ===========================================================================" << endl;
	cout << "\t   �۾� ���� : ";
	cin >> command;
	return command;
}

void MusicFile::DisplayMusicInfo() {
	using namespace std;

	cout << endl;
	cout << "\t  ===============" << endl;
	cout << "\t  || ���� ���� ||" << endl;
	cout << "\t  ===========================================================================" << endl;
	cout << "\t    ���� �̸� : " << title << endl;
	cout << "\t    ��Ƽ��Ʈ �� : " << artist << endl;
	cout << "\t    �ٹ� �� : " << album << endl;
	cout << "\t  ===========================================================================" << endl;
}