#include <set>
#include "computer.h"
#include "chessboard1v1.h"

Computer::Computer(shared_ptr<ChessBoard> board, int color, int level) :
	Player(board, color), level(level) {}

int Computer::getRandom(int low, int high) {
	return (rd() - rd.min()) % (high - low + 1) + low;
}

vector<int> Computer::getNextMove() {
	vector<int> move;
	auto real_board = board.lock();
	vector<vector<int>> moves;
	set<pair<int, int>> other_reach;
	int count = 0;
	for (auto piece : *real_board) {
		count++;
		vector<vector<int>> new_moves = piece->getMoves();
		if (piece->getColor() == color) {
			for (auto &move : new_moves) {
				if (!real_board->doesMoveSelfCheck(move)) {
					moves.push_back(move);
				}
			}
		} else {
			for (auto &move : new_moves) {
				other_reach.insert({move[2], move[3]});
			}
		}
	}
	if (level >= 4) {
		// do advanced stuff
		// return answer
	}
	vector<vector<int>> preferred_moves;
	if (level >= 2) {
		for (auto &move : moves) {
			if (real_board->getPiece(move[2], move[3])) { // capture
				preferred_moves.push_back(move);
				continue;
			}
			// check/checkmate
			real_board->processMove(move);
			if (real_board->getState() == ChessBoard1V1::CHECK ||
				real_board->getState() == ChessBoard1V1::CHECKMATE) {
				preferred_moves.push_back(move);
				real_board->undo();
				continue;
			}
			// avoid capture
			if (level == 3) {
				if (!other_reach.count({move[0], move[1]})) {
					real_board->undo();
					continue;
				}
				vector<vector<int>> other_moves;
				for (auto piece : *real_board) {
					if (piece->getColor() != color) {
						auto cur_moves = piece->getMoves();
						other_moves.insert(other_moves.end(), cur_moves.begin(), cur_moves.end());
					}
				}
				bool good = true;
				for (auto &move2 : other_moves) {
					if (move2[2] == move[2] && move2[3] == move[3]) {
						good = false;
						break;
					}
				}
				if (good) {
					preferred_moves.push_back(move);
				}
			}
			real_board->undo();
		}
	}
	if (!preferred_moves.empty()) {
		moves = preferred_moves;
	}
	int sz = moves.size(), index = getRandom(0, sz - 1);
	return moves[index];
}
