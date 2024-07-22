#ifndef PLAYER_H
#define PLAYER_H

class Player {
private:
	bool black;
	int wins;

public:
	virtual void makeNextMove() = 0;
};

#endif