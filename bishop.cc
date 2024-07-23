#include "bishop.h"

const vector<pair<int, int>> DIRS = {{1, -1}, {-1, 1}, {1, 1}, {-1, -1}};
const char WHITE_CHAR = 'B', BLACK_CHAR = 'b';

Bishop::Bishop(shared_ptr<ChessBoard> board, int row, int col, int color) :
	ChessPiece(board, row, col, color, WHITE_CHAR, BLACK_CHAR) {}

void Bishop::display() {

}

vector<pair<int, int>> Bishop::getMoves() {
	return dirMoves(DIRS);
}
