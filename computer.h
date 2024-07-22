#ifndef COMPUTER_H
#define COMPUTER_H
#include "player.h"

class Computer : public Player {
public:
	void makeNextMove() override;
};

#endif
