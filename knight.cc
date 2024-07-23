#include "knight.h"

const vector<pair<int, int>> OFFSETS = {{1, 2}, {2, 1}, {-1, 2}, {1, -2}, {2, -1}, {-2, 1}, {-2, -1}, {-1, -2}};

Knight::Knight(shared_ptr<ChessBoard> board, int row, int col, int color) :
	ChessPiece(board, row, col, color, WHITE_CHAR, BLACK_CHAR) {}

void Knight::display() {

}

vector<vector<int>> Knight::getMoves() {
	return offsetMoves(OFFSETS);
}
