#include <vector>
#include "king.h"

const vector<pair<int, int>> OFFSETS = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
const char WHITE_CHAR = 'K', BLACK_CHAR = 'k';

King::King(shared_ptr<ChessBoard> board, int row, int col, int color) :
	ChessPiece(board, row, col, color, WHITE_CHAR, BLACK_CHAR), hasMoved(false) {}

void King::display() {
	
}

vector<pair<int, int>> King::getMoves() {
	vector<pair<int, int>> ans = ChessPiece::offsetMoves(OFFSETS);
	// add castling move
	return ans;
}

void King::moveTo(int row, int col) {
	hasMoved = true;
	ChessPiece::moveTo(row, col);
}
