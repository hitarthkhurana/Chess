#include "player.h"

Player::Player(shared_ptr<ChessBoard> board, int color) :
	board(board), color(color), wins(0) {}
