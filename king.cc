#include <vector>
#include "king.h"

const vector<pair<int, int>> OFFSETS = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

King::King(shared_ptr<ChessBoard>, int row, int col, int color) :
	board(board, row, col, color), hasMoved(false) {}

void King::display() {
	
}

vector<pair<int, int>> King::getMoves() {
	vector<pair<int, int>> ans = ChessPiece::offsetMoves(OFFSETS, color);
	// add castling move
	return ans;
}

void King::moveTo(int row, int col) {
	hasMoved = true;
	ChessPiece::moveTo(row, col);
}
