#include <set>
#include "pawn.h"
#include "player.h"

const set<int> ENPASSANT_ROWS = {3, 4};

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

	// Add capture moves
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

	// Add en passant moves
	if (real_board->validPos(row, col - 1)) {
		auto pawn = dynamic_pointer_cast<Pawn>(real_board->getPiece(row, col - 1));
		if (pawn && pawn->getColor() != color && pawn->enPassantAllowed()) {
			ans.push_back({row, col, row + add, col - 1, true});
		}
	}
	if (real_board->validPos(row, col + 1)) {
		auto pawn = dynamic_pointer_cast<Pawn>(real_board->getPiece(row, col + 1));
		if (pawn && pawn->getColor() != color && pawn->enPassantAllowed()) {
			ans.push_back({row, col, row + add, col + 1, true});
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

bool Pawn::enPassantAllowed() const {
	// En passant allowed if one move, appropriate row, and last move was this piece's move
	if (moveCnt != 1 || !ENPASSANT_ROWS.count(row)) {
		return false;
	}
	auto move = board.lock()->getLastMove();
	return move.r2 == row && move.c2 == col;
}
