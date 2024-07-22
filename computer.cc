#include "computer.h"

Computer::Computer(shared_ptr<ChessBoard> board, int color) :
	Player(board, color) {}

void Computer::makeNextMove() {
	// board. ...
}
