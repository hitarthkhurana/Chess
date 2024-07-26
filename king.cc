#include <set>
#include "king.h"
#include "rook.h"
#include "chessboard1v1.h"

const vector<pair<int, int>> OFFSETS = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
const vector<pair<int, int>> CASTLE_DIRS = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

King::King(shared_ptr<ChessBoard> board, int row, int col, int color) :
	ChessPiece(board, row, col, color, WHITE_CHAR, BLACK_CHAR), moveCnt(0) {}

vector<Move> King::getMoves() const {
	vector<Move> ans = ChessPiece::offsetMoves(OFFSETS);
	auto real_board = board.lock();
	// If the king has not moved, check in needed direction for a rook that can
	// be castled with
	if (moveCnt == 0) {
		for (auto [a, b] : CASTLE_DIRS) {
			int row2 = row + a, col2 = col + b;
			while (real_board->validPos(row2, col2)) {
				auto piece = real_board->getPiece(row2, col2);
				if (piece) {
					auto rook = dynamic_pointer_cast<Rook>(piece);
					if (rook && !rook->hasMoved() && rook->getColor() == color) {
						ans.push_back({
							row, col, row + a + a, col + b + b,
							row2, col2, row + a, col + b
						});
					}
					break;
				}
				row2 += a;
				col2 += b;
			}
		}
	}
	return ans;
}

void King::setPos(int row, int col, bool undo) {
	ChessPiece::setPos(row, col);
	// Increase move count, but decrease instead for undo
	moveCnt += undo ? -1 : 1;
}

bool King::hasMoved() const {
	return moveCnt != 0;
}
