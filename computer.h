#ifndef COMPUTER_H
#define COMPUTER_H
#include <random>
#include "player.h"

using namespace std;

class Computer : public Player {
private:
	random_device rd;
	int level;
	int getRandom(int low, int high);

public:
	Computer(shared_ptr<ChessBoard> board, int color, int level);
	Move getNextMove();
};

#endif
