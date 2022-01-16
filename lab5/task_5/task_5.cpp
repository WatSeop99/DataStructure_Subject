#include <Windows.h>
#include "Application.h"

void MainPage() {
	using namespace std;

	system("title 탐색기");
	cout << "\n\n\n\n";
	cout << "          ===========================================================================" << endl;
	cout << "                     #####   #   #   ####    #         #     ####    #####" << endl;
	cout << "                     #        # #    #   #   #       ## ##   #   #   #" << endl;
	cout << "                     ####      #     ####    #       #   #   # ##    ####" << endl;
	cout << "                     #        # #    #       #       ## ##   # #     #" << endl;
	cout << "                     #####   #   #   #       #####     #     #  ##   #####" << endl;
	cout << endl;
	cout << "                                 1. Run Exporor" << endl;
	cout << "                                 2. Quit" << endl;
}

int GetCommand() {
	int command;
	cout << "                                    choice : ";
	cin >> command;
	return command;
}

void RunProgram(Application& app) {
	int command, count = 0;
	MainPage();
	command = GetCommand();
	while (true) {
		if (command == 1) {
			cin.clear();
			cout << "          ===========================================================================" << endl << endl << endl << endl;
			app.Run();
			break;
		}
		else if (command == 2) {
			cin.clear();
			cout << "          ===========================================================================" << endl;
			break;
		}
		else {
			cin.clear();
			cout << "                          invalid selection." << endl;
			count++;
		}
		if (count == 4) {
			cout << "\t Because of more than 5 input, Program will be shutdown." << endl;
			break;
		}
		command = GetCommand();
	}
}

int main() {
	system("color 3F");
	Application app;
	RunProgram(app);
	return 0;
}