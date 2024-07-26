#include "bishop.h"

const vector<pair<int, int>> DIRS = {{1, -1}, {-1, 1}, {1, 1}, {-1, -1}};

Bishop::Bishop(shared_ptr<ChessBoard> board, int row, int col, int color) :
	ChessPiece(board, row, col, color, WHITE_CHAR, BLACK_CHAR) {}

vector<Move> Bishop::getMoves() const {
	return dirMoves(DIRS);
}
