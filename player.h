#ifndef PLAYER_H
#define PLAYER_H
#include <memory>
#include "chessboard.h"

using namespace std;

class ChessBoard;

class Player {
protected:
	int color;                  // Color of player's pieces
	weak_ptr<ChessBoard> board; // Keep track of the board

public:
	// Create a Player from a string
	static shared_ptr<Player> fromString(const string &s, shared_ptr<ChessBoard> board, int color);

	// Allowed colors for the player
	enum Colors {
		BLACK = 0, WHITE
	};

	virtual ~Player() = default; // Make sure the class is polymorphic
	Player(shared_ptr<ChessBoard> board, int color);
	bool getColor() const;
};

#endif
