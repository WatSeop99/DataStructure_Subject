#include "MusicFile.h"

void MusicFile::SetRecord() {
	std::string input;
	std::cout << "\t  음원 제목 입력 : ";
	std::cin >> input;
	SetTitle(input);
	input.clear();
	std::cout << "\t  아티스트 입력 : ";
	std::cin >> input;
	SetArtist(input);
	input.clear();
	std::cout << "\t  앨범 입력 : ";
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
	cout << "\t  || Music 파일 작업 메뉴 ||" << endl;
	cout << "\t  ===========================================================================" << endl;
	cout << "\t     1.  Music 파일 정보 출력" << endl;
	cout << "\t     2.  Music 파일 종료" << endl;
	cout << "\t  ===========================================================================" << endl;
	cout << "\t   작업 선택 : ";
	cin >> command;
	return command;
}

void MusicFile::DisplayMusicInfo() {
	using namespace std;

	cout << endl;
	cout << "\t  ===============" << endl;
	cout << "\t  || 현재 음악 ||" << endl;
	cout << "\t  ===========================================================================" << endl;
	cout << "\t    음악 이름 : " << title << endl;
	cout << "\t    아티스트 명 : " << artist << endl;
	cout << "\t    앨범 명 : " << album << endl;
	cout << "\t  ===========================================================================" << endl;
}