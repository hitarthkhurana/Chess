#include <set>
#include "king.h"
#include "rook.h"
#include "chessboard1v1.h"

const vector<pair<int, int>> OFFSETS = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
const vector<pair<int, int>> CASTLE_DIRS = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

King::King(shared_ptr<ChessBoard> board, int row, int col, int color) :
	ChessPiece(board, row, col, color, WHITE_CHAR, BLACK_CHAR), moveCnt(0) {}

vector<vector<int>> King::getMoves() {
	vector<vector<int>> ans = ChessPiece::offsetMoves(OFFSETS);
	auto real_board = board.lock();
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
	/*vector<vector<int>> adjusted_ans;
	set<pair<int, int>> bad_targets;
	for (auto piece : *real_board) {
		if (piece->getColor() == color) {
			continue;
		}
		auto king = dynamic_pointer_cast<King>(piece);
		if (king) {
			continue;
		}
		for (auto move : piece->getMoves()) {
			int sz = move.size();
			for (int i = 0; i < sz; i += MOVE_SIZE) {
				bad_targets.insert({move[i + 2], move[i + 3]});
			}
		}
	}
	// consts?
	for (auto move : ans) {
		if (!bad_targets.count({move[2], move[3]})) {
			adjusted_ans.push_back(move);
		}
	}
	return adjusted_ans;*/
}

void King::setPos(int row, int col, bool undo) {
	ChessPiece::setPos(row, col);
	moveCnt += undo ? -1 : 1;
}

bool King::hasMoved() {
	return moveCnt != 0;
}
