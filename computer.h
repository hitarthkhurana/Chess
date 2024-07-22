#ifndef COMPUTER_H
#define COMPUTER_H
#include "player.h"

class Computer : public Player {
public:
	Computer(shared_ptr<ChessBoard> board, int color);
	void makeNextMove() override;
};

#endif
