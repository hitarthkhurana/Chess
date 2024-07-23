#include "chessboard.h"

ChessBoard::ChessBoard(shared_ptr<Xwindow> window, int player_cnt, int size) :
	Displayable(window),
	moveCnt(0),
	players(player_cnt),
	cells(size),
	pieces(size, vector<shared_ptr<ChessPiece>> (size)) {

	for (int i = 0; i < size; i++) {
		cells[i].resize(size);
	}
}

void ChessBoard::reset() {}

shared_ptr<ChessPiece> ChessBoard::getPiece(int row, int col) {
	return pieces[row - 1][col - 1];
}

void ChessBoard::setPlayer(int index, shared_ptr<Player> player) {
	players[index - 1] = player;
}

void ChessBoard::placePiece(const string &piece, const string &position) {
	// do something
}
