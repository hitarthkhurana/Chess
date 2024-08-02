#include "chesscell.h"
#include "chessboard1v1.h"
#include "king.h"
#include "pawn.h"

// Standard chess board constants
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
	// Get the current and next moves
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
	// See if the king is in check
	bool check = false;
	shared_ptr<King> king;
	for (auto &move : next_moves) {
		king = dynamic_pointer_cast<King>(pieces[move.r2][move.c2]);
		if (king) {
			check = true;
			break;
		}
	}
	// Determine the state of the board
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
	ChessBoard(window, PLAYER_CNT, SIZE, NORMAL), hasInit(false), displayed(false) {}

void ChessBoard1V1::init() {
	// Set the cells and pieces as needed
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
	// Return the board to its initial configuration
	init();
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			auto piece = ChessPiece::fromString(
				string(1, PLACEMENTS[SIZE - i - 1][j]),
				shared_from_this(),
				i, j
			);
			if (!piece && !pieces[i][j]) {
				continue;
			}
			pieces[i][j] = piece;
		}
	}
	while (!removedPieces.empty()) {
		removedPieces.pop();
	}
	while (!allMoves.empty()) {
		allMoves.pop();
	}
	state = NORMAL;
	moveCnt = 0;
}

void ChessBoard1V1::clear() {
	// Clear the board of all its pieces
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (!pieces[i][j]) {
				continue;
			}
			pieces[i][j] = shared_ptr<ChessPiece>();
		}
	}
}

void ChessBoard1V1::display() {
	// Display the board, cell by cell
	init();
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (displayed && lastDisplayPieces[i][j] == pieces[i][j]) {
				continue;
			}
			lastDisplayPieces[i][j] = pieces[i][j];
			if (cells[i][j]) {
				cells[i][j]->display();
				if (pieces[i][j]) {
					pieces[i][j]->display();
				}
			}
		}
	}
	displayed = true;
}

void ChessBoard1V1::print() {
	// Print the board, cell by cell, along with its axes
	init();
	for (int i = SIZE - 1; i >= 0; i--) {
		// Print the left axis
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
	// Print the bottom axis
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
	// Not a valid setup if either king is in check
	init();
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
	// Ensure exactly one king for each color and no pawns in first or last row
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

pair<int, int> ChessBoard1V1::getCoords(int row, int col) const {
	return {col * CELL_SIZE, (SIZE - row - 1) * CELL_SIZE};
}
