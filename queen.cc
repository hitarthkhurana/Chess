#include "queen.h"

const vector<pair<int, int>> DIRS = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

Queen::Queen(shared_ptr<ChessBoard>, int row, int col, int color) :
	board(board, row, col, color) {}

void Queen::display() {

}

vector<pair<int, int>> Queen::getMoves() {
	return dirMoves(DIRS);
}
