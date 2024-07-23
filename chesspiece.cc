#include "chesspiece.h"
#include "player.h"

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

void ChessPiece::moveTo(int row, int col) {
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
