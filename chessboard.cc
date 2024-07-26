#include "chessboard.h"
#include "chessboard1v1.h"
#include "computer.h"
#include "king.h"

void ChessBoard::setPiece(int row, int col, shared_ptr<ChessPiece> piece) {
	pieces[row][col] = piece;
	updated[row][col] = true;
}

ChessBoard::ChessBoard(shared_ptr<Xwindow> window, int playerCnt, int size, int state) :
	Displayable(window),
	moveCnt(0), state(state),
	players(playerCnt),
	cells(size),
	pieces(size, vector<shared_ptr<ChessPiece>> (size)),
	updated(size, vector<bool> (size, true)) {

	for (int i = 0; i < size; i++) {
		cells[i].resize(size);
	}
}

shared_ptr<ChessPiece> ChessBoard::getPiece(int row, int col) const {
	return pieces[row][col];
}

void ChessBoard::setPlayer(int index, shared_ptr<Player> player) {
	players[index - 1] = player;
}

shared_ptr<Player> ChessBoard::getPlayer(int index) const {
	return players[index - 1];
}

void ChessBoard::placePiece(shared_ptr<ChessPiece> piece, int row, int col) {
	setPiece(row, col, piece);
}

void ChessBoard::removePiece(int row, int col) {
	setPiece(row, col, shared_ptr<ChessPiece>());
}

void ChessBoard::setTurn(int color) {
	if (color != getCurrentPlayer()->getColor()) {
		moveCnt++;
	}
}

bool ChessBoard::doesMoveSelfCheck(const Move &move) {
	// Try the move and see whether the king is in the path of the opposing
	// player's pieces
	moveCnt--;
	processMove(move, false);
	bool ans = false;
	int color = players[moveCnt % players.size()]->getColor();
	for (auto piece : *this) {
		if (piece->getColor() != color) {
			auto moves = piece->getMoves();
			for (auto &cur_move : moves) {
				auto piece2 = pieces[cur_move.r2][cur_move.c2];
				if (auto king = dynamic_pointer_cast<King>(piece2); king && king->getColor() == color) {
					ans = true;
					break;
				}
			}
			if (ans) {
				break;
			}
		}
	}
	moveCnt++;
	undo(false);
	return ans;
}

int ChessBoard::tryMove(int r1, int c1, int r2, int c2, int promotion) {
	// Attempt the given move and see if it is valid. Return an appropriate error
	// if invalid.
	if (pieces[r1][c1]->getColor() != getCurrentPlayer()->getColor()) {
		return BAD_TURN;
	}
	auto moves = pieces[r1][c1]->getMoves();
	int index = -1, sz = moves.size();
	for (int i = 0; i < sz; i++) {
		auto &move = moves[i];
		if (move.r1 == r1 && move.c1 == c1 && move.r2 == r2 && move.c2 == c2) {
			if (move.promotion != promotion) {
				return BAD_PROMOTION;
			}
			index = i;
			break;
		}
	}
	if (index == -1) {
		return OTHER;
	} else if (doesMoveSelfCheck(moves[index])) {
		return SELF_CHECK;
	}
	processMove(moves[index]);
	return NONE;
}

shared_ptr<Player> ChessBoard::getCurrentPlayer() const {
	return players[moveCnt % players.size()];
}

bool ChessBoard::undo(bool stateUpdate) {
	// Undo te last move by retracing the steps made
	if (allMoves.empty()) {
		return false;
	}
	auto &move = allMoves.top();
	int r1 = move.r1, c1 = move.c1, r2 = move.r2, c2 = move.c2;
	if (move.enPassant) {
		setPiece(r1, c2, removedPieces.top());
		removedPieces.pop();
	} else if (move.promotion != Move::NONE) {
		pieces[r2][c2] = removedPieces.top();
		removedPieces.pop();
	} else if (move.castle) {
		int r3 = move.r3, c3 = move.c3, r4 = move.r4, c4 = move.c4;
		setPiece(r3, c3, pieces[r4][c4]);
		pieces[r3][c3]->setPos(r3, c3, true);
		setPiece(r4, c4, removedPieces.top());
		removedPieces.pop();
	}
	setPiece(r1, c1, pieces[r2][c2]);
	pieces[r1][c1]->setPos(r1, c1, true);
	setPiece(r2, c2, removedPieces.top());
	removedPieces.pop();
	allMoves.pop();
	moveCnt--;
	if (stateUpdate) {
		updateState();
	}
	return true;
}

void ChessBoard::processMove(const Move &move, bool stateUpdate) {
	// Make the requested move, along with castling and pawn promotion if applicable
	int r1 = move.r1, c1 = move.c1, r2 = move.r2, c2 = move.c2;
	removedPieces.push(pieces[r2][c2]);
	setPiece(r2, c2, pieces[r1][c1]);
	pieces[r2][c2]->setPos(r2, c2);
	setPiece(r1, c1, shared_ptr<ChessPiece>());
	if (move.castle) {
		int r3 = move.r3, c3 = move.c3, r4 = move.r4, c4 = move.c4;
		removedPieces.push(pieces[r4][c4]);
		setPiece(r4, c4, pieces[r3][c3]);
		pieces[r4][c4]->setPos(r4, c4);
		setPiece(r3, c3, shared_ptr<ChessPiece>());
	} else if (move.promotion != Move::NONE) {
		removedPieces.push(pieces[r2][c2]);
		pieces[r2][c2] = ChessPiece::fromPromotion(move.promotion, shared_from_this(),
			r2, c2, removedPieces.top()->getColor());
	} else if (move.enPassant) {
		removedPieces.push(pieces[r1][c2]);
		setPiece(r1, c2, shared_ptr<ChessPiece>());
	}
	allMoves.push(move);
	moveCnt++;
	if (stateUpdate) {
		updateState();
	}
}

void ChessBoard::makeComputerMove() {
	// Make the computer's move, if it is the computer's turn
	int sz = players.size();
	shared_ptr<Player> cur_player = players[moveCnt % sz];
	shared_ptr<Computer> computer = dynamic_pointer_cast<Computer>(cur_player);
	if (computer) {
		auto move = computer->getNextMove();
		processMove(move);
	}
}

Move ChessBoard::getLastMove() const {
	return allMoves.top();
}

int ChessBoard::getState() const {
	return state;
}

ChessBoard::Iterator::Iterator(shared_ptr<ChessBoard> board, int i, int j) :
	board(board), i(i), j(j) {}

ChessBoard::Iterator& ChessBoard::Iterator::operator++() {
	// Increment until a piece is reached in the board
	int sz = board->pieces.size();
	while (true) {
		j++;
		if (j == sz) {
			j = 0;
			i++;
		}
		if (i == sz || board->pieces[i][j]) {
			break;
		}
	}
	return *this;
}

shared_ptr<ChessPiece> ChessBoard::Iterator::operator*() const {
	return board->pieces[i][j];
}

bool ChessBoard::Iterator::operator==(const Iterator &other) const {
	// Determine equality from the boards and positions
	return board == other.board && i == other.i && j == other.j;
}

ChessBoard::Iterator ChessBoard::begin() {
	return ++Iterator(shared_from_this(), 0, -1);
}

ChessBoard::Iterator ChessBoard::end() {
	return Iterator(shared_from_this(), pieces.size(), 0);
}
