#ifndef COMPUTER_H
#define COMPUTER_H
#include <random>
#include "player.h"

using namespace std;

class Computer : public Player {
private:
	random_device rd; // Randomizer object
	int level;        // Level of play difficulty

	int getRandom(int low, int high); // Return a random number between high and low

public:
	Computer(shared_ptr<ChessBoard> board, int color, int level);
	Move getNextMove(); // Get the next move of the player
};

#endif
