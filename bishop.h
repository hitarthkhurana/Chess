#ifndef BISHOP_H
#define BISHOP_H
#include <memory>
#include <vector>
#include <utility>
#include "chesspiece.h"
#include "chessboard.h"

using namespace std;

class Bishop : public ChessPiece {
public:
	Bishop(shared_ptr<ChessBoard>, int row, int col, int color);
	void display() override;
	vector<pair<int, int>> getMoves() override;
};

#endif
