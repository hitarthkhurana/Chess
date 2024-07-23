#ifndef PAWN_H
#define PAWN_H
#include <memory>
#include <vector>
#include <utility>
#include "chessboard.h"
#include "chesspiece.h"

using namespace std;

class Pawn : public ChessPiece {
public:
	Pawn(shared_ptr<ChessBoard>, int row, int col, int color);
	void display() override;
	vector<pair<int, int>> getMoves() override;
};

#endif
