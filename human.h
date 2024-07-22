#ifndef HUMAN_H
#define HUMAN_H
#include "player.h"

class Human : public Player {
public:
	Human(shared_ptr<ChessBoard> board, int color);
	void makeNextMove() override;
};

#endif
