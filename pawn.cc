#include "pawn.h"
#include "player.h"

Pawn::Pawn(shared_ptr<ChessBoard> board, int row, int col, int color) :
	ChessPiece(board, row, col, color, WHITE_CHAR, BLACK_CHAR), moveCnt(0) {}

vector<Move> Pawn::getMoves() const {
	// Determine direction of movement
	int add = color == Player::WHITE ? 1 : -1;

	auto real_board = board.lock();
	if (!real_board->validPos(row + add, col)) {
		return {};
	}

	// Add regular pawn moves
	vector<Move> ans;
	if (!real_board->getPiece(row + add, col)) {
		ans.push_back({row, col, row + add, col});
		if (moveCnt == 0 && !real_board->getPiece(row + 2 * add, col)) {
			ans.push_back({row, col, row + 2 * add, col});
		}
	}

	// Add en passant moves
	if (real_board->validPos(row + add, col + 1)) {
		auto piece = real_board->getPiece(row + add, col + 1);
		if (piece && piece->getColor() != color) {
			ans.push_back({row, col, row + add, col + 1});
		}
	}
	if (real_board->validPos(row + add, col - 1)) {
		auto piece = real_board->getPiece(row + add, col - 1);
		if (piece && piece->getColor() != color) {
			ans.push_back({row, col, row + add, col - 1});
		}
	}

	// Apply promotions to moves, if applicable
	if (!real_board->validPos(row + add + add, col)) {
		vector<Move> real_ans;
		for (int promotion : {Move::QUEEN, Move::ROOK, Move::BISHOP, Move::KNIGHT}) {
			for (auto move : ans) {
				move.promotion = promotion;
				real_ans.push_back(move);
			}
		}
		ans = move(real_ans);
	}
	return ans;
}

void Pawn::setPos(int row, int col, bool undo) {
	ChessPiece::setPos(row, col);
	// Increase move count, but decrease instead for undo
	moveCnt += undo ? -1 : 1;
}
