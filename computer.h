#ifndef COMPUTER_H
#define COMPUTER_H
#include "player.h"

class Computer : public Player {
private:
	int level;

public:
	Computer(shared_ptr<ChessBoard> board, int color, int level);
	void makeNextMove() override;
};

#endif
