#include "chessboard.h"
#include "computer.h"

const int MOVE_SIZE = 4;

void ChessBoard::setPiece(int row, int col, shared_ptr<ChessPiece> piece) {
	pieces[row][col] = piece;
	updated[row][col] = true;
}

void ChessBoard::makeComputerMoves() {
	int sz = players.size();
	while (true) {
		shared_ptr<Player> cur_player = players[moveCnt % sz];
		shared_ptr<Computer> computer = dynamic_pointer_cast<Computer>(cur_player);
		if (computer) {
			auto move = computer->getNextMove();
			processMove(move);
			moveCnt++;
		} else {
			break;
		}
	}
}

void ChessBoard::processMove(const vector<int> &move) {
	int sz = move.size();
	for (int i = 0; i < sz; i += MOVE_SIZE) {
		int a = move[i], b = move[i + 1], c = move[i + 2], d = move[i + 3];
		removed_pieces.push(pieces[c][d]);
		setPiece(c, d, pieces[a][b]);
		pieces[c][d]->setPos(c, d);
		setPiece(a, b, shared_ptr<ChessPiece>());
	}
}

ChessBoard::ChessBoard(shared_ptr<Xwindow> window, int player_cnt, int size) :
	Displayable(window),
	moveCnt(0),
	players(player_cnt),
	cells(size),
	pieces(size, vector<shared_ptr<ChessPiece>> (size)),
	updated(size, vector<bool> (size, true)) {

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

void ChessBoard::placePiece(const string &piece, const string &pos) {
	int row = pos[1] - '1', col = pos[0] - 'a';
	setPiece(row, col, ChessPiece::fromString(piece, shared_from_this(), row, col));
}

void ChessBoard::removePiece(const string &pos) {
	setPiece(pos[1] - '1', pos[0] - 'a', shared_ptr<ChessPiece>());
}

bool ChessBoard::setTurn(const string &color) {
	int color_num;
	if (color == "white") { // make const?
		color_num = Player::WHITE;
	} else if (color == "black") {
		color_num = Player::BLACK;
	} else {
		return false;
	}
	int sz = players.size();
	for (int i = 0; i < sz; i++) {
		auto &player = players[i];
		if (player->getColor() == color_num) {
			moveCnt = i;
			break;
		}
	}
	return true;
}

bool ChessBoard::hasValidSetup() {return 1;}

bool ChessBoard::move(const string &from, const string &to, const string &promotion) {
	// need to account for promotion
	int r1 = from[1] - '1', c1 = from[0] - 'a', r2 = to[1] - '1', c2 = to[0] - 'a';
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
	moveCnt++;
	all_moves.push(moves[index]);
	processMove(moves[index]);
	makeComputerMoves();
	return true;
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
		setPiece(a, b, pieces[c][d]);
		setPiece(c, d, removed_pieces.top());
		removed_pieces.pop();
	}
	all_moves.pop();
	return true;
}

ChessBoard::Iterator::Iterator(shared_ptr<ChessBoard> board, int i, int j) :
	board(board), i(i), j(j) {}

ChessBoard::Iterator& ChessBoard::Iterator::operator++() {
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

shared_ptr<ChessPiece> ChessBoard::Iterator::operator*() {
	return board->pieces[i][j];
}

bool ChessBoard::Iterator::operator==(const Iterator &other) {
	return board == other.board && i == other.i && j == other.j;
}

ChessBoard::Iterator ChessBoard::begin() {
	return ++Iterator(shared_from_this(), 0, -1);
}

ChessBoard::Iterator ChessBoard::end() {
	return Iterator(shared_from_this(), pieces.size(), 0);
}
