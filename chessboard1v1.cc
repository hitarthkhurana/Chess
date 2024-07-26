#include "chesscell.h"
#include "chessboard1v1.h"
#include "king.h"
#include "pawn.h"

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
	"RNBQKBNR"
};

void ChessBoard1V1::updateState() {
	vector<Move> cur_moves, next_moves;
	int color = getCurrentPlayer()->getColor();
	for (auto piece : *this) {
		auto new_moves = piece->getMoves();
		if (piece->getColor() == color) {
			for (auto &move : new_moves) {
				if (!doesMoveSelfCheck(move)) {
					cur_moves.push_back(move);
				}
			}
		} else {
			next_moves.insert(next_moves.end(), new_moves.begin(), new_moves.end());
		}
	}
	bool check = false;
	shared_ptr<King> king;
	for (auto &move : next_moves) {
		king = dynamic_pointer_cast<King>(pieces[move.r2][move.c2]);
		if (king) {
			check = true;
			break;
		}
	}
	if (check) {
		if (cur_moves.empty()) {
			state = CHECKMATE; 
		} else {
			state = CHECK;
		}
	} else if (cur_moves.empty()) {
		state = STALEMATE;
	} else {
		state = NORMAL;
	}
}

ChessBoard1V1::ChessBoard1V1(shared_ptr<Xwindow> window) :
	ChessBoard(window, PLAYER_CNT, SIZE, NORMAL), hasInit(false) {}

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
	while (!removed_pieces.empty()) {
		removed_pieces.pop();
	}
	while (!all_moves.empty()) {
		all_moves.pop();
	}
	state = NORMAL;
	moveCnt = 0;
}

void ChessBoard1V1::clear() {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (!pieces[i][j]) {
				continue;
			}
			updated[i][j] = true;
			pieces[i][j] = shared_ptr<ChessPiece>();
		}
	}
}

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
		cout << static_cast<char> (COL_START + i);
	}
	cout << endl;
}

bool ChessBoard1V1::validPos(int row, int col) {
	init();
	return 0 <= row && row < SIZE && 0 <= col && col < SIZE;
}

bool ChessBoard1V1::hasValidSetup() {
	bool white_king = false, black_king = false;
	updateState();
	if (state == CHECK || state == CHECKMATE) {
		return false;
	}
	moveCnt++;
	updateState();
	if (state == CHECK || state == CHECKMATE) {
		moveCnt--;
		updateState();
		return false;
	}
	moveCnt--;
	updateState();
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			auto king = dynamic_pointer_cast<King>(pieces[i][j]);
			if (king) {
				bool &has_king = king->getColor() == Player::WHITE ? white_king : black_king;
				if (has_king) {
					return false;
				}
				has_king = true;
			 } else if ((i == 0 || i == SIZE - 1) && dynamic_pointer_cast<Pawn>(pieces[i][j])) {
				 return false;
			 }
		}
	}
	return white_king && black_king;
}

pair<int, int> ChessBoard1V1::getCoords(int row, int col) {
	return {col * CELL_SIZE, (SIZE - row - 1) * CELL_SIZE};
}
