#include "bishop.h"

const vector<pair<int, int>> DIRS = {{1, -1}, {-1, 1}, {1, 1}, {-1, -1}};

Bishop::Bishop(shared_ptr<ChessBoard>, int row, int col, int color) :
	board(board, row, col, color), hasMoved(false) {}

void Bishop::display() {

}

vector<pair<int, int>> Bishop::getMoves() {
	return dirMoves(DIRS);
}
