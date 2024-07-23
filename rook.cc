#include "rook.h"

const vector<pair<int, int>> DIRS = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
const char WHITE_CHAR = 'R', BLACK_CHAR = 'r';

Rook::Rook(shared_ptr<ChessBoard> board, int row, int col, int color) :
	ChessPiece(board, row, col, color, WHITE_CHAR, BLACK_CHAR), hasMoved(false) {}

void Rook::display() {

}

vector<pair<int, int>> Rook::getMoves() {
	vector<pair<int, int>> ans = dirMoves(DIRS);
	// add castling move
	return ans;
}

void Rook::moveTo(int row, int col) {
	hasMoved = true;
	ChessPiece::moveTo(row, col);
}
