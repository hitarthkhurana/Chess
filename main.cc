#include <iostream>
#include "gamemanager.h"
#include "chessboard1v1.h"

using namespace std;

int main() {
	GameManager gm;
	string line;
	while (getline(cin, line)) {
		gm.processCommand(line);
	}
}
