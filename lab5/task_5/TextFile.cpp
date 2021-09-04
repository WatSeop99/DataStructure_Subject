#include "TextFile.h"

void TextFile::Run(std::string name) {
	std::cout << "\t  run..." << std::endl;
	int command;
	while (true) {
		command = GetCommand();
		switch (command) {
		case 1:
			ReadText(name);
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

int TextFile::GetCommand() {
	using namespace std;

	int command;
	cout << endl;
	cout << "\t  =========================" << endl;
	cout << "\t  || Text 파일 작업 메뉴 ||" << endl;
	cout << "\t  ===========================================================================" << endl;
	cout << "\t     1.  txt파일 읽어오기" << endl;
	cout << "\t     2.  txt파일 새로 쓰기(덮어쓰기)" << endl;
	cout << "\t     3.  기존 txt파일에 덧붙여 쓰기" << endl;
	cout << "\t     4.  파일 실행 종료" << endl;
	cout << "\t  ===========================================================================" << endl;
	cout << "\t   작업 선택 : ";
	cin >> command;
	return command;
}

bool TextFile::ReadText(std::string name) {
	using namespace std;

	inFile.open(name+".txt");
	if (!inFile) return false;
	cout << endl;
	cout << "\t  ====================" << endl;
	cout << "\t  || Text 파일 내용 ||" << endl;
	cout << "\t  ===========================================================================" << endl;
	string line;
	while (getline(inFile, line))
		cout << "\t     " << line << endl;
	cout << "\t  ===========================================================================" << endl;
	cout << endl;
	inFile.close();
	return true;
}

bool TextFile::WriteText(std::string name, int command) {
	using namespace std;

	if (command == 2) {
		outFile.open(name+".txt");
		cout << endl;
		cout << "\t  ===========================" << endl;
		cout << "\t  || 입력할 Text 파일 내용 ||" << endl;
		cout << "\t  ===========================================================================" << endl;
		cout << "\t     입력 (q 입력 시 종료) : ";
		string line;
		while (getline(cin, line)) {
			if (line == "q") break;
			outFile << line << '\n';
			cout << "\t     ";
		}
	}
	else {
		outFile.open(name+".txt", ios::app);
		if (!outFile) return false;
		cout << endl;
		cout << "\t  ===========================" << endl;
		cout << "\t  || 입력할 Text 파일 내용 ||" << endl;
		cout << "\t  ===========================================================================" << endl;
		cout << "\t     입력 (q 입력 시 종료) : ";
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