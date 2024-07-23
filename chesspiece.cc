#include "chesspiece.h"
#include "rook.h"
#include "king.h"
#include "queen.h"
#include "bishop.h"
#include "pawn.h"
#include "knight.h"
#include "player.h"

shared_ptr<ChessPiece> ChessPiece::fromString(const string &s, shared_ptr<ChessBoard> board, int row, int col) {
	switch (s[0]) {
		case Rook::WHITE_CHAR:
			return make_shared<Rook>(board, row, col, Player::WHITE);
		case Rook::BLACK_CHAR:
			return make_shared<Rook>(board, row, col, Player::BLACK);
		case King::WHITE_CHAR:
			return make_shared<King>(board, row, col, Player::WHITE);
		case King::BLACK_CHAR:
			return make_shared<King>(board, row, col, Player::BLACK);
		case Queen::WHITE_CHAR:
			return make_shared<Queen>(board, row, col, Player::WHITE);
		case Queen::BLACK_CHAR:
			return make_shared<Queen>(board, row, col, Player::BLACK);
		case Bishop::WHITE_CHAR:
			return make_shared<Bishop>(board, row, col, Player::WHITE);
		case Bishop::BLACK_CHAR:
			return make_shared<Bishop>(board, row, col, Player::BLACK);
		case Pawn::WHITE_CHAR:
			return make_shared<Pawn>(board, row, col, Player::WHITE);
		case Pawn::BLACK_CHAR:
			return make_shared<Pawn>(board, row, col, Player::BLACK);
		case Knight::WHITE_CHAR:
			return make_shared<Knight>(board, row, col, Player::WHITE);
		case Knight::BLACK_CHAR:
			return make_shared<Knight>(board, row, col, Player::BLACK);
		default:
			return shared_ptr<ChessPiece>();
	}
}

ChessPiece::ChessPiece(shared_ptr<ChessBoard> board, int row, int col, int color, char white_char, char black_char) :
	Displayable(board->getWindow()), board(board), row(row), col(col),
	color(color), white_char(white_char), black_char(black_char) {}

vector<pair<int, int>> ChessPiece::offsetMoves(const vector<pair<int, int>> &offsets) {
	vector<pair<int, int>> ans;
	auto real_board = board.lock();
	for (auto [a, b] : offsets) {
		int row2 = row + a, col2 = col + b;
		if (real_board->validPos(row2, col2)) {
			auto piece = real_board->getPiece(row2, col2);
			if (!piece || piece->color != color) {
				ans.push_back({row2, col2});
			}
		}
	}
	return ans;
}

vector<pair<int, int>> ChessPiece::dirMoves(const vector<pair<int, int>> &dirs) {
	vector<pair<int, int>> ans;
	auto real_board = board.lock();
	for (auto [a, b] : dirs) {
		int row2 = row + a, col2 = col + b;
		while (real_board->validPos(row2, col2)) {
			auto piece = real_board->getPiece(row2, col2);
			if (!piece || piece->color != color) {
				ans.push_back({row2, col2});
			}
			if (piece) {
				break;
			}
			row2 += a;
			col2 += b;
		}
	}
	return ans;
}

void ChessPiece::setPos(int row, int col) {
	this->row = row;
	this->col = col;
}

void ChessPiece::print() {
	if (color == Player::WHITE) {
		cout << white_char;
	} else {
		cout << black_char;
	}
}

int ChessPiece::getColor() {
	return color;
}
