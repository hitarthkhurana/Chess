#include "rook.h"
#include "king.h"

const vector<pair<int, int>> DIRS = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
const vector<pair<int, int>> CASTLE_DIRS = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
const int CASTLE_SIZE = 8, CASTLE_IND1 = 4, CASTLE_IND2 = 5;

Rook::Rook(shared_ptr<ChessBoard> board, int row, int col, int color) :
	ChessPiece(board, row, col, color, WHITE_CHAR, BLACK_CHAR), moveCnt(0) {}

vector<vector<int>> Rook::getMoves() {
	vector<vector<int>> ans = dirMoves(DIRS);
	auto real_board = board.lock();
	if (moveCnt == 0) {
		for (auto [a, b] : CASTLE_DIRS) {
			int row2 = row + a, col2 = col + b;
			while (real_board->validPos(row2, col2)) {
				auto piece = real_board->getPiece(row2, col2);
				if (piece) {
					auto king = dynamic_pointer_cast<King>(piece);
					if (king && king->getColor() == color) {
						auto king_moves = king->getMoves();
						for (auto &move : king_moves) {
							if (move.size() == CASTLE_SIZE && move[4] == CASTLE_IND1 && move[5] == CASTLE_IND2) {
								ans.push_back(move);
							}
						}
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

void Rook::setPos(int row, int col, bool undo) {
	ChessPiece::setPos(row, col);
	moveCnt += undo ? -1 : 1;
}

bool Rook::hasMoved() {
	return moveCnt != 0;
}
