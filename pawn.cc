#include "pawn.h"
#include "player.h"

Pawn::Pawn(shared_ptr<ChessBoard> board, int row, int col, int color) :
	ChessPiece(board, row, col, color, WHITE_CHAR, BLACK_CHAR), moveCnt(0) {}

vector<vector<int>> Pawn::getMoves() {
	int row2 = row, col2 = col;
	if (color == Player::WHITE) {
		row2++;
	} else {
		row2--;
	}
	auto real_board = board.lock();
	if (!real_board->validPos(row2, col2)) {
		return {};
	}
	vector<vector<int>> ans;
	if (!real_board->getPiece(row2, col2)) {
		ans.push_back({row, col, row2, col2});
		int row3 = (row2 - row) * 2 + row, col3 = (col2 - col) * 2 + col;
		if (moveCnt == 0 && !real_board->getPiece(row3, col3)) {
			ans.push_back({row, col, row3, col3});
		}
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

void Pawn::setPos(int row, int col, bool undo) {
	ChessPiece::setPos(row, col);
	moveCnt += undo ? -1 : 1;
}
