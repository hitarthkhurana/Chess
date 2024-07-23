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
	return pieces[row][col];
}

void ChessBoard::setPlayer(int index, shared_ptr<Player> player) {
	players[index - 1] = player;
}

void ChessBoard::placePiece(shared_ptr<ChessPiece> piece, int r, int c) {
	piece->setPos(r, c);
	pieces[r][c] = piece;
}

void ChessBoard::placePiece(const string &piece, const string &pos) {
	placePiece(ChessPiece::fromString(piece, shared_from_this()), pos[1] - '1', pos[0] - 'a');
}

void ChessBoard::move(int r1, int c1, int r2, int c2) {
	// temporary measure
	cout << r1 << ' ' << c1 << ' ' << r2 << ' ' << c2 << endl;
	swap(pieces[r1][c1], pieces[r2][c2]);
}

void ChessBoard::move(const string &from, const string &to, const string &promotion) {
	move(from[1] - '1', from[0] - 'a', to[1] - '1', to[0] - 'a');
}
