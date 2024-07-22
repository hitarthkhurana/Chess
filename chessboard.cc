#include "chessboard.h"

ChessBoard::ChessBoard(shared_ptr<Xwindow> window) :
	Displayable(window), moveCnt(0) {}

void ChessBoard::reset() {}

shared_ptr<ChessPiece> ChessBoard::getPiece(int row, int col) {
	return pieces[row - 1][col - 1];
}
