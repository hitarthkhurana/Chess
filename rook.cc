#include "rook.h"
#include "king.h"

const vector<pair<int, int>> DIRS = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
const vector<pair<int, int>> CASTLE_DIRS = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

Rook::Rook(shared_ptr<ChessBoard> board, int row, int col, int color) :
	ChessPiece(board, row, col, color, WHITE_CHAR, BLACK_CHAR), moveCnt(0) {}

vector<Move> Rook::getMoves() {
	vector<Move> ans = dirMoves(DIRS);
	return ans;
}

void Rook::setPos(int row, int col, bool undo) {
	ChessPiece::setPos(row, col);
	moveCnt += undo ? -1 : 1;
}

bool Rook::hasMoved() {
	return moveCnt != 0;
}
