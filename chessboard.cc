#include "chessboard.h"

const int MOVE_SIZE = 4;

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

shared_ptr<ChessPiece> ChessBoard::getPiece(int row, int col) {
	return pieces[row][col];
}

void ChessBoard::setPlayer(int index, shared_ptr<Player> player) {
	players[index - 1] = player;
}

void ChessBoard::placePiece(shared_ptr<ChessPiece> piece, int row, int col) {
	piece->setPos(row, col);
	pieces[row][col] = piece;
}

void ChessBoard::placePiece(const string &piece, const string &pos) {
	placePiece(ChessPiece::fromString(piece, shared_from_this()), pos[1] - '1', pos[0] - 'a');
}

void ChessBoard::removePiece(int row, int col) {
	pieces[row][col] = shared_ptr<ChessPiece>();
}

void ChessBoard::removePiece(const string &pos) {
	removePiece(pos[1] - '1', pos[0] - 'a');
}

void ChessBoard::setTurn(int color) {
	int sz = players.size();
	for (int i = 0; i < sz; i++) {
		auto &player = players[i];
		if (player->getColor() == color) {
			moveCnt = i;
			break;
		}
	}
}

bool ChessBoard::setTurn(const string &color) {
	if (color == "white") {
		setTurn(Player::WHITE);
	} else if (color == "black") {
		setTurn(Player::BLACK);
	} else {
		return false;
	}
	return true;
}

bool ChessBoard::hasValidSetup() {return 1;}

bool ChessBoard::move(int r1, int c1, int r2, int c2) {
	if (!validPos(r1, c1) || !validPos(r2, c2) || !pieces[r1][c1]) {
		return false;
	}
	if (pieces[r1][c1]->getColor() != getCurrentPlayer()->getColor()) {
		return false;
	}
	auto moves = pieces[r1][c1]->getMoves();
	int sz = moves.size(), sz2, index = -1;
	for (int i = 0; i < sz && index == -1; i++) {
		auto &move = moves[i];
		sz2 = move.size();
		for (int j = 0; j < sz2; j += MOVE_SIZE) {
			int a = move[j], b = move[j + 1], c = move[j + 2], d = move[j + 3];
			if (a == r1 && b == c1 && c == r2 && d == c2) {
				index = i;
				break;
			}
		}
	}
	if (index == -1) {
		return false;
	}
	for (int i = 0; i < sz2; i += MOVE_SIZE) {
		auto &move = moves[index];
		int a = move[i], b = move[i + 1], c = move[i + 2], d = move[i + 3];
		removed_pieces.push(pieces[c][d]);
		pieces[c][d] = pieces[a][b];
		pieces[c][d]->setPos(c, d);
		pieces[a][b] = shared_ptr<ChessPiece>();
	}
	moveCnt++;
	all_moves.push(moves[index]);
	return true;
}

bool ChessBoard::move(const string &from, const string &to, const string &promotion) {
	return move(from[1] - '1', from[0] - 'a', to[1] - '1', to[0] - 'a');
}

shared_ptr<Player> ChessBoard::getCurrentPlayer() {
	return players[moveCnt % players.size()];
}

bool ChessBoard::undo() {
	if (all_moves.empty()) {
		return false;
	}
	auto &move = all_moves.top();
	int sz = move.size();
	for (int i = sz - MOVE_SIZE; i >= 0; i -= MOVE_SIZE) {
		int a = move[i], b = move[i + 1], c = move[i + 2], d = move[i + 3];
		pieces[a][b] = pieces[c][d];
		pieces[c][d] = removed_pieces.top();
		removed_pieces.pop();
	}
	all_moves.pop();
	return true;
}
