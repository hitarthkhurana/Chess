#include "player.h"

Player::Player(shared_ptr<ChessBoard> board, int color) :
	color(color), wins(0), board(board) {}
