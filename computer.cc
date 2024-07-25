#include <set>
#include "computer.h"
#include "chessboard1v1.h"

Computer::Computer(shared_ptr<ChessBoard> board, int color, int level) :
	Player(board, color), level(level) {}

int Computer::getRandom(int low, int high) {
	return (rd() - rd.min()) % (high - low + 1) + low;
}

const int P = 100, N = 320, B = 330, R = 500, Q = 900, K = 20000;

// Array representation for point-square tables (evaluation matrices)
const int pawn_table[8][8] = {
    { 0,  0,  0,  0,  0,  0,  0,  0},
    {50, 50, 50, 50, 50, 50, 50, 50},
    {10, 10, 20, 30, 30, 20, 10, 10},
    { 5,  5, 10, 25, 25, 10,  5,  5},
    { 0,  0,  0, 20, 20,  0,  0,  0},
    { 5, -5,-10,  0,  0,-10, -5,  5},
    { 5, 10, 10,-20,-20, 10, 10,  5},
    { 0,  0,  0,  0,  0,  0,  0,  0}
};

const int knight_table[8][8] = {
    {-50,-40,-30,-30,-30,-30,-40,-50},
    {-40,-20,  0,  0,  0,  0,-20,-40},
    {-30,  0, 10, 15, 15, 10,  0,-30},
    {-30,  5, 15, 20, 20, 15,  5,-30},
    {-30,  0, 15, 20, 20, 15,  0,-30},
    {-30,  5, 10, 15, 15, 10,  5,-30},
    {-40,-20,  0,  5,  5,  0,-20,-40},
    {-50,-40,-30,-30,-30,-30,-40,-50}
};

const int bishop_table[8][8] = {
    {-20,-10,-10,-10,-10,-10,-10,-20},
    {-10,  0,  0,  0,  0,  0,  0,-10},
    {-10,  0,  5, 10, 10,  5,  0,-10},
    {-10,  5,  5, 10, 10,  5,  5,-10},
    {-10,  0, 10, 10, 10, 10,  0,-10},
    {-10, 10, 10, 10, 10, 10, 10,-10},
    {-10,  5,  0,  0,  0,  0,  5,-10},
    {-20,-10,-10,-10,-10,-10,-10,-20}
};

const int rook_table[8][8] = {
    { 0,  0,  0,  0,  0,  0,  0,  0},
    { 5, 10, 10, 10, 10, 10, 10,  5},
    {-5,  0,  0,  0,  0,  0,  0, -5},
    {-5,  0,  0,  0,  0,  0,  0, -5},
    {-5,  0,  0,  0,  0,  0,  0, -5},
    {-5,  0,  0,  0,  0,  0,  0, -5},
    {-5,  0,  0,  0,  0,  0,  0, -5},
    { 0,  0,  0,  5,  5,  0,  0,  0}
};

const int queen_table[8][8] = {
    {-20,-10,-10, -5, -5,-10,-10,-20},
    {-10,  0,  0,  0,  0,  0,  0,-10},
    {-10,  0,  5,  5,  5,  5,  0,-10},
    { -5,  0,  5,  5,  5,  5,  0, -5},
    {  0,  0,  5,  5,  5,  5,  0, -5},
    {-10,  5,  5,  5,  5,  5,  0,-10},
    {-10,  0,  5,  0,  0,  0,  0,-10},
    {-20,-10,-10, -5, -5,-10,-10,-20}
};

const int king_table[8][8] = {
    {-30,-40,-40,-50,-50,-40,-40,-30},
    {-30,-40,-40,-50,-50,-40,-40,-30},
    {-30,-40,-40,-50,-50,-40,-40,-30},
    {-30,-40,-40,-50,-50,-40,-40,-30},
    {-20,-30,-30,-40,-40,-30,-30,-20},
    {-10,-20,-20,-20,-20,-20,-20,-10},
    { 20, 20,  0,  0,  0,  0, 20, 20},
    { 20, 30, 10,  0,  0, 10, 30, 20}
};

int getPieceValue(shared_ptr<ChessPiece> piece) {
    if (!piece) return 0;
    switch (piece->getType()) {
        case ChessPiece::PAWN: return P;
        case ChessPiece::KNIGHT: return N;
        case ChessPiece::BISHOP: return B;
        case ChessPiece::ROOK: return R;
        case ChessPiece::QUEEN: return Q;
        case ChessPiece::KING: return K;
        default: return 0;
    }
}

int getPieceSquareValue(shared_ptr<ChessPiece> piece, int row, int col) {
    if (!piece) return 0;
    int score = 0;
    switch (piece->getType()) {
        case ChessPiece::PAWN: score = pawn_table[row][col]; break;
        case ChessPiece::KNIGHT: score = knight_table[row][col]; break;
        case ChessPiece::BISHOP: score = bishop_table[row][col]; break;
        case ChessPiece::ROOK: score = rook_table[row][col]; break;
        case ChessPiece::QUEEN: score = queen_table[row][col]; break;
        case ChessPiece::KING: score = king_table[row][col]; break;
        default: break;
    }
    return piece->getColor() == Player::WHITE ? score : -score;
}

int evaluateBoard(shared_ptr<ChessBoard> board) {
    int score = 0;
    for (auto& piece : *board) {
        int row = piece->getRow();
        int col = piece->getCol();
        score += getPieceValue(piece) + getPieceSquareValue(piece, row, col);
    }
    return score;
}

vector<int> Computer::getNextMove() {
	vector<int> move;
	auto real_board = board.lock();
	vector<vector<int>> moves;
	set<pair<int, int>> other_reach;
	int count = 0;
	for (auto piece : *real_board) {
		count++;
		vector<vector<int>> new_moves = piece->getMoves();
		if (piece->getColor() == color) {
			for (auto &move : new_moves) {
				if (!real_board->doesMoveSelfCheck(move)) {
					moves.push_back(move);
				}
			}
		} else {
			for (auto &move : new_moves) {
				other_reach.insert({move[2], move[3]});
			}
		}
	}
	if (level >= 4) {
		// do advanced stuff
		// return answer
	}
	vector<vector<int>> preferred_moves;
	if (level >= 2) {
		for (auto &move : moves) {
			if (real_board->getPiece(move[2], move[3])) { // capture
				preferred_moves.push_back(move);
				continue;
			}
			// check/checkmate
			real_board->processMove(move);
			if (real_board->getState() == ChessBoard1V1::CHECK ||
				real_board->getState() == ChessBoard1V1::CHECKMATE) {
				preferred_moves.push_back(move);
				real_board->undo();
				continue;
			}
			// avoid capture
			if (level == 3) {
				if (!other_reach.count({move[0], move[1]})) {
					real_board->undo();
					continue;
				}
				vector<vector<int>> other_moves;
				for (auto piece : *real_board) {
					if (piece->getColor() != color) {
						auto cur_moves = piece->getMoves();
						other_moves.insert(other_moves.end(), cur_moves.begin(), cur_moves.end());
					}
				}
				bool good = true;
				for (auto &move2 : other_moves) {
					if (move2[2] == move[2] && move2[3] == move[3]) {
						good = false;
						break;
					}
				}
				if (good) {
					preferred_moves.push_back(move);
				}
			}
			real_board->undo();
		}
	}
	if (!preferred_moves.empty()) {
		moves = preferred_moves;
	}
	int sz = moves.size(), index = getRandom(0, sz - 1);
	return moves[index];
}
