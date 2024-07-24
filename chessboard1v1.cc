#include "chesscell.h"
#include "chessboard1v1.h"
#include "king.h"

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

void ChessBoard1V1::updateStatus() {
	vector<vector<int>> cur_moves, next_moves;
	int color = getCurrentPlayer()->getColor();
	for (auto piece : *this) {
		auto new_moves = piece->getMoves();
		auto &moves = piece->getColor() == color ? cur_moves : next_moves;
		moves.insert(moves.end(), new_moves.begin(), new_moves.end());
	}
	bool check = false;
	shared_ptr<King> king;
	for (auto &move : next_moves) {
		int sz = move.size();
		for (int i = 0; i < sz; i += MOVE_SIZE) {
			int a = move[i + 2], b = move[i + 3];
			king = dynamic_pointer_cast<King>(pieces[a][b]);
			if (king) {
				check = true;
				break;
			}
		}
		if (check) {
			break;
		}
	}
	if (check) {
		auto king_moves = king->getMoves();
		if (king_moves.empty()) {
			status = CHECKMATE; 
		} else {
			status = CHECK;
		}
	} else if (cur_moves.empty()) {
		status = STALEMATE;
	} else {
		status = NORMAL;
	}
}

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
			updated[i][j] = true;
			pieces[i][j] = ChessPiece::fromString(
				string(1, PLACEMENTS[SIZE - i - 1][j]),
				shared_from_this(),
				i, j
			);
		}
	}
}

// move methods to ChessBoard for 4 player
void ChessBoard1V1::display() {
	init();
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (!updated[i][j]) {
				continue;
			}
			updated[i][j] = false;
			if (cells[i][j]) {
				cells[i][j]->display();
				if (pieces[i][j]) {
					pieces[i][j]->display();
				}
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
			} else if (cells[i][j]) {
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
