#include "chesscell.h"
#include "chessboard1v1.h"
#include "rook.h"

const int SIZE = 8;
const int PLAYER_CNT = 2;

ChessBoard1V1::ChessBoard1V1(shared_ptr<Xwindow> window) :
	ChessBoard(window, PLAYER_CNT, SIZE), hasInit(false) {}

void ChessBoard1V1::init() {
	if (hasInit) {
		return;
	}
	hasInit = true;
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			cells[i][j] = make_unique<ChessCell>(shared_from_this(), (i + j) % 2);
		}
	}
	pieces[5][5] = make_shared<Rook>(shared_from_this(), 6, 6, 1);
}

void ChessBoard1V1::display() {
	init();
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
	init();
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

bool ChessBoard1V1::validPos(int row, int col) {
	init();
	return 1 <= row && row <= SIZE && 1 <= col && col <= SIZE;
}
