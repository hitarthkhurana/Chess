#include "queen.h"

const vector<pair<int, int>> DIRS = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

Queen::Queen(shared_ptr<ChessBoard> board, int row, int col, int color) :
	ChessPiece(board, row, col, color, WHITE_CHAR, BLACK_CHAR) {}

void Queen::display() {

}

vector<vector<int>> Queen::getMoves() {
	return dirMoves(DIRS);
}
