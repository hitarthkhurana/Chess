#ifndef PLAYER_H
#define PLAYER_H
#include <memory>
#include "chessboard.h"

using namespace std;

class ChessBoard;

class Player {
protected:
	int color, wins;
	weak_ptr<ChessBoard> board;

public:
	virtual ~Player() = default;
	static shared_ptr<Player> fromString(const string &s, shared_ptr<ChessBoard> board, int color);
	enum Colors {
		BLACK = 0, WHITE, BLUE, GREEN, YELLOW, RED
	};

	Player(shared_ptr<ChessBoard> board, int color);
	bool getColor();
	int getWins();
	void incrementWins();
};

#endif
