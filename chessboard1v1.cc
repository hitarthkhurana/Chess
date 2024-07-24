#include "chesscell.h"
#include "chessboard1v1.h"
#include "rook.h"

const int SIZE = 8;
const int PLAYER_CNT = 2;
const int CELL_SIZE = 90;
const vector<string> PLACEMENTS = {
	"rnbqkbnr",
	"pppppppp",
	"--------",
	"--------",
	"--------",
	"--------",
	"PPPPPPPP",
	"RNBKQBNR"
};

ChessBoard1V1::ChessBoard1V1(shared_ptr<Xwindow> window) :
	ChessBoard(window, PLAYER_CNT, SIZE), hasInit(false) {}

void ChessBoard1V1::init() {
	if (hasInit) {
		return;
	}
	hasInit = true;
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			cells[i][j] = make_unique<ChessCell>(
				shared_from_this(),
				i, j,
				(i + j) % 2 ? ChessCell::LIGHT : ChessCell::DARK,
				CELL_SIZE
			);
				
		}
	}
	reset();
}

void ChessBoard1V1::reset() {
	init();
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			pieces[i][j] = ChessPiece::fromString(
				string(1, PLACEMENTS[SIZE - i - 1][j]),
				shared_from_this(),
				i, j
			);
		}
	}
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
	for (int i = SIZE - 1; i >= 0; i--) {
		cout << (i + 1) << " ";
		for (int j = 0; j < SIZE; j++) {
			if (pieces[i][j]) {
				pieces[i][j]->print();
			} else {
				cells[i][j]->print();
			}
		}
		cout << endl;
	}
	cout << endl << "  ";
	for (int i = 0; i < SIZE; i++) {
		cout << static_cast<char> ('a' + i);
	}
	cout << endl;
}

bool ChessBoard1V1::validPos(int row, int col) {
	init();
	return 0 <= row && row < SIZE && 0 <= col && col < SIZE;
}

pair<int, int> ChessBoard1V1::getCoords(int row, int col) {
	return {col * CELL_SIZE, (SIZE - row - 1) * CELL_SIZE};
}
