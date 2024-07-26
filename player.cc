#include "player.h"
#include "human.h"
#include "computer.h"
#include "chessboard.h"

shared_ptr<Player> Player::fromString(const string &s, shared_ptr<ChessBoard> board, int color) {
	// Return the correct type of Player represented by s
	if (s[0] == 'h') {
		return make_shared<Human>(board, color);
	} else {
		int level = s.back() - '0';
		return make_shared<Computer>(board, color, level);
	}
}

Player::Player(shared_ptr<ChessBoard> board, int color) :
	color(color), board(board) {}

bool Player::getColor() const {
	return color;
}
