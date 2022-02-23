#include "Application.h"

void mainPage() {
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

int getCommand() {
	int command;
	std::cout << "                                    choice : ";
	std::cin >> command;
	return command;
}

void runProgram(Application& app) {
	int command, count = 0;
	mainPage();
	command = getCommand();
	while (true) {
		if (command == 1) {
			std::cin.clear();
			std::cout << "          ===========================================================================" << std::endl << std::endl << std::endl << std::endl;
			app.run();
			break;
		}
		else if (command == 2) {
			std::cin.clear();
			std::cout << "          ===========================================================================" << std::endl;
			break;
		}
		else {
			std::cin.clear();
			std::cout << "                          invalid selection." << std::endl;
			count++;
		}
		if (count == 4) {
			std::cout << "\t Because of more than 5 input, Program will be shutdown." << std::endl;
			break;
		}
		command = getCommand();
	}
}

int main() {
	system("color 3F");
	Application app;
	runProgram(app);
	return 0;
}