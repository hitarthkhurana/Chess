#ifndef PLAYER_H
#define PLAYER_H
#include <memory>
#include "chessboard.h"

using namespace std;

class ChessBoard;

class Player {
protected:
	int color, wins;
	shared_ptr<ChessBoard> board;

public:
	enum Colors {
		BLACK = 0, WHITE, BLUE, GREEN, YELLOW, RED
	};

	Player(shared_ptr<ChessBoard> board, int color);
	virtual void makeNextMove() = 0;
};

#endif
