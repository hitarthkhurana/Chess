#include "knight.h"

const vector<pair<int, int>> OFFSETS = {{1, 2}, {2, 1}, {-1, 2}, {1, -2}, {2, -1, {-2, 1}, {-2, -1}, {-1, -2}};

King::King(shared_ptr<ChessBoard>, int row, int col, int color) :
	board(board, row, col, color) {}

Knight::display() {

}

vector<pair<int, int>> Knight::getMoves() {
	return offsetMoves(OFFSETS);
}
