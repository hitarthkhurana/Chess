#include "chesspiece.h"
#include "player.h"

ChessPiece::ChessPiece(shared_ptr<ChessBoard>, int row, int col, int color) :
	board(board), row(row), col(col), color(color) {}

vector<pair<int, int>> ChessPiece::offsetMoves(const vector<pair<int, int>> &offsets) {
	vector<pair<int, int>> ans;
	for (auto [a, b] : offsets) {
		int row2 = row + a, col2 = col + b;
		if (board->validPos(row2, col2)) {
			auto piece = board->pieceAt(row2, col2);
			if (!piece || piece.getColor() != color) {
				ans.push_back({row2, col2});
			}
		}
	}
	return ans;
}

vector<pair<int, int>> ChessPiece::dirMoves(const vector<pair<int, int>> &dirs) {
	vector<pair<int, int>> ans;
	for (auto [a, b] : dirs) {
		int row2 = row + a, col2 = col + b;
		while (board->validPos(row2, col2)) {
			auto piece = board->pieceAt(row2, col2);
			if (!piece || piece.getColor() != color) {
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
		cout << WHITE_CHAR;
	} else {
		cout << BLACK_CHAR;
	}
}
