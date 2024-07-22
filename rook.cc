#include "rook.h"

const vector<pair<int, int>> DIRS = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

Rook::Rook(shared_ptr<ChessBoard>, int row, int col, int color) :
	board(board, row, col, color), hasMoved(false) {}

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
