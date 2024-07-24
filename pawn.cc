#include "pawn.h"
#include "player.h"

Pawn::Pawn(shared_ptr<ChessBoard> board, int row, int col, int color) :
	ChessPiece(board, row, col, color, WHITE_CHAR, BLACK_CHAR) {}

vector<vector<int>> Pawn::getMoves() {
	// wrong logic currently
	int row2 = row, col2 = col;
	if (color == Player::WHITE) {
		row2++;
	} else {
		row2--;
	}
	auto real_board = board.lock();
	vector<vector<int>> ans;
	if (!real_board->getPiece(row2, col2)) {
		ans.push_back({row, col, row2, col2});
	}
	if (real_board->validPos(row2, col2 + 1)) {
		auto piece = real_board->getPiece(row2, col2 + 1);
		if (piece && piece->getColor() != color) {
			ans.push_back({row, col, row2, col2 + 1});
		}
	}
	if (real_board->validPos(row2, col2 - 1)) {
		auto piece = real_board->getPiece(row2, col2 - 1);
		if (piece && piece->getColor() != color) {
			ans.push_back({row, col, row2, col2 - 1});
		}
	}
	return ans;
}
