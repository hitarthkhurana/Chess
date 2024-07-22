#include "chessboard1v1.h"
#include "rook.h"

const int SIZE = 8;
const int PLAYERS = 2;

ChessBoard1V1::ChessBoard1V1(shared_ptr<Xwindow> window) :
	ChessBoard(window),
	cells(SIZE, vector<unique_ptr<ChessCell>> (SIZE)),
	pieces(SIZE, vector<unique_ptr<ChessPiece>> (SIZE)) {

	// initialize players
	
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			cells[i][j] = new ChessCell((i + j) % 2);
		}
	}
	pieces[5][5] = new Rook(this, 1);
}

void ChessBoard1V1::display() {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			cells[i][j]->display();
			if (pieces[i][j]) {
				pieces[i][j]->display();
			}
		}
	}
}

void ChessBoard1V1::print() {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (pieces[i][j]) {
				pieces[i][j]->print();
			} else {
				cells[i][j]->print();
			}
		}
	}
}

bool ChessBoard::validPos(int row, int col) {
	return 1 <= row && row <= SIZE && 1 <= col && col <= SIZE;
}
