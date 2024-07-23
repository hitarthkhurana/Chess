#include "pawn.h"
#include "player.h"

const char WHITE_CHAR = 'P', BLACK_CHAR = 'p';

Pawn::Pawn(shared_ptr<ChessBoard> board, int row, int col, int color) :
	ChessPiece(board, row, col, color, WHITE_CHAR, BLACK_CHAR) {}

void Pawn::display() {

}

vector<pair<int, int>> Pawn::getMoves() {
	// wrong logic currently
	int row2 = row, col2 = col;
	if (color == Player::WHITE) {
		row2++;
	} else {
		row2--;
	}
	if (board.lock()->validPos(row2, col2)) {
		return {{row2, col2}};
	} else {
		return {};
	}
}
