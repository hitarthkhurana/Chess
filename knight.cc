#include "knight.h"

const vector<pair<int, int>> OFFSETS = {{1, 2}, {2, 1}, {-1, 2}, {1, -2}, {2, -1}, {-2, 1}, {-2, -1}, {-1, -2}};
const char WHITE_CHAR = 'N', BLACK_CHAR = 'n';

Knight::Knight(shared_ptr<ChessBoard> board, int row, int col, int color) :
	ChessPiece(board, row, col, color, WHITE_CHAR, BLACK_CHAR) {}

void Knight::display() {

}

vector<pair<int, int>> Knight::getMoves() {
	return offsetMoves(OFFSETS);
}
