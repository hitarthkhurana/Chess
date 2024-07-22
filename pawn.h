#ifndef PAWN_H
#define PAWN_H
#include <memory>
#include <vector>
#include <utility>
#include "chessboard.h"
#include "chesspiece.h"

using namespace std;

class Pawn : public ChessPiece {
protected:
	const char WHITE_CHAR = 'P', BLACK_CHAR = 'p';

public:
	Pawn(shared_ptr<ChessBoard>, int row, int col, int color);
	void display() override;
	void print() override;
	vector<pair<int, int>> getMoves() override;
}

#endif
