#include "computer.h"

Computer::Computer(shared_ptr<ChessBoard> board, int color, int level) :
	Player(board, color), level(level) {}

int Computer::getRandom(int low, int high) {
	return (rd() - rd.min()) % (high - low + 1) + low;
}

vector<int> Computer::getNextMove() {
	vector<int> move;
	auto real_board = board.lock();
	if (level == 1) {
		vector<vector<int>> moves;
		int count = 0;
		for (auto piece : *real_board) {
			count++;
			if (piece->getColor() != color) {
				continue;
			}
			vector<vector<int>> new_moves = piece->getMoves();
			for (auto &move : new_moves) {
				if (!real_board->isMoveCheck(move)) {
					moves.push_back(move);
				}
			}
		}
		int sz = moves.size(), index = getRandom(0, sz - 1);
		move = moves[index];
	}
	return move;
}
