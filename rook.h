#ifndef ROOK_H
#define ROOK_H
#include <memory>
#include <vector>
#include <utility>
#include "chesspiece.h"
#include "chessboard.h"

using namespace std;

class Rook : public ChessPiece {
private:
	bool hasMoved;

public:
	Rook(shared_ptr<ChessBoard>, int row, int col, int color);
	void display() override;
	vector<pair<int, int>> getMoves() override;
	void setPos(int row, int col) override;
};

#endif
