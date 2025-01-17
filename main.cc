#include <iostream>
#include "gamemanager.h"
#include "chessboard1v1.h"

const string PROMPT = " >>> ";

using namespace std;

int main() {
	// Process commands until there is no more, or the program is quit
	cout << "Welcome to C++-Chess!" << endl;
	cout << "Enter a command to continue." << endl;

	GameManager gm;
	string line;
	cout << PROMPT;
	while (getline(cin, line)) {
		cout << endl;
		if (!gm.processCommand(line)) {
			break;
		}
		cout << endl << PROMPT;
	}

	cout << endl << endl;
	gm.printScore();
	cout << endl << "Bye!" << endl;
}
