#include "chessboard.h"

ChessBoard::ChessBoard() : moveCnt(0) {}

void ChessBoard::reset() {}

shared_ptr<ChessPiece> ChessBoard::getPiece(int row, int col) {
	return pieces[row - 1][col - 1];
}
