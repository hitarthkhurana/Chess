#include "pawn.h"

Pawn::Pawn(shared_ptr<ChessBoard>, int row, int col, int color) :
	board(board, row, col, color) {}

void Pawn::display() {

}

vector<pair<int, int>> Pawn::getMoves() {
	// wrong logic currently
	int row2 = row, col2 = col;
	if (color == ChessPiece::WHITE) {
		row2++;
	} else {
		row2--;
	}
	if (board->validPos(row2, col2)) {
		return {{row2, col2}};
	} else {
		return {};
	}
}
