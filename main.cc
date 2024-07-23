#include <iostream>
#include "gamemanager.h"
#include "chessboard1v1.h"

const string PROMPT = " >>> ";

using namespace std;

int main() {
	cout << "Welcome to C++-Chess!" << endl;
	cout << "Enter a command to continue" << endl;

	GameManager gm;
	string line;
	cout << PROMPT;
	while (getline(cin, line)) {
		cout << endl;
		gm.processCommand(line);
		cout << endl << PROMPT;
	}
}
