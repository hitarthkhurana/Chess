#include "computer.h"

Computer::Computer(shared_ptr<ChessBoard> board, int color, int level) :
	Player(board, color), level(level) {}

void Computer::makeNextMove() {
	// board. ...
}
