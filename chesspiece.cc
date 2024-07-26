#include "chesspiece.h"
#include "rook.h"
#include "king.h"
#include "queen.h"
#include "bishop.h"
#include "pawn.h"
#include "knight.h"
#include "player.h"

const string ASSETS_DIR = "./assets/";
const string LIGHT_PREFIX = "l";
const string DARK_PREFIX = "d";
const vector<string> COLOR_PREFIXES = {"b", "w"};

shared_ptr<ChessPiece> ChessPiece::fromString(const string &s, shared_ptr<ChessBoard> board, int row, int col) {
	// Match the character in s to the appropriate type of ChessPiece
	if (s.size() != 1) {
		return shared_ptr<ChessPiece>();
	}
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

shared_ptr<ChessPiece> ChessPiece::fromPromotion(int promotion, shared_ptr<ChessBoard> board, int row, int col, int color) {
	// Match the given promotion to the appropriate type of ChessPiece
	shared_ptr<ChessPiece> ans;
	switch (promotion) {
		case Move::QUEEN:
			ans = make_shared<Queen>(board, row, col, color);
			break;
		case Move::ROOK:
			ans = make_shared<Rook>(board, row, col, color);
			break;
		case Move::BISHOP:
			ans = make_shared<Bishop>(board, row, col, color);
			break;
		case Move::KNIGHT:
			ans = make_shared<Knight>(board, row, col, color);
			break;
		default:
			ans = shared_ptr<ChessPiece>();
			break;
	}
	// Simulate a move to ensure non-zero move count
	if (ans) {
		ans->setPos(row, col);
	}
	return ans;
}

ChessPiece::ChessPiece(shared_ptr<ChessBoard> board, int row, int col, int color, char white_char, char black_char) :
	Displayable(board->getWindow()), board(board), row(row), col(col),
	color(color), white_char(white_char), black_char(black_char) {}

vector<Move> ChessPiece::offsetMoves(const vector<pair<int, int>> &offsets) const {
	// Return a list of all valid moves using offsets from the current position
	vector<Move> ans;
	auto real_board = board.lock();
	for (auto [a, b] : offsets) {
		int row2 = row + a, col2 = col + b;
		if (real_board->validPos(row2, col2)) {
			auto piece = real_board->getPiece(row2, col2);
			if (!piece || piece->color != color) {
				ans.push_back({row, col, row2, col2});
			}
		}
	}
	return ans;
}

vector<Move> ChessPiece::dirMoves(const vector<pair<int, int>> &dirs) const {
	// Return a list of all valid moves using directions from the current position
	vector<Move> ans;
	auto real_board = board.lock();
	for (auto [a, b] : dirs) {
		int row2 = row + a, col2 = col + b;
		while (real_board->validPos(row2, col2)) {
			auto piece = real_board->getPiece(row2, col2);
			if (!piece || piece->color != color) {
				ans.push_back({row, col, row2, col2});
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

void ChessPiece::setPos(int row, int col, bool undo) {
	this->row = row;
	this->col = col;
}

void ChessPiece::print() {
	// Print a character depending on the player color
	if (color == Player::WHITE) {
		cout << white_char;
	} else {
		cout << black_char;
	}
}

void ChessPiece::display() {
	// Generate the appropriate file name, and display the image from it
	string filename = ASSETS_DIR;
	filename += (row + col) % 2 ? LIGHT_PREFIX : DARK_PREFIX;
	filename += COLOR_PREFIXES[color];
	filename += black_char;
	auto [x, y] = board.lock()->getCoords(row, col);
	window->drawImage(x, y, filename);
}

int ChessPiece::getColor() const {
	return color;
}

pair<int, int> ChessPiece::getPos() const {
	return {row, col};
}
