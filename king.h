#ifndef KING_H
#define KING_H
#include <memory>
#include <vector>
#include <utility>
#include "chesspiece.h"
#include "chessboard.h"

using namespace std;

class King : public ChessPiece {
private:
	bool hasMoved;

public:
	King(shared_ptr<ChessBoard>, int row, int col, int color);
	void display() override;
	vector<pair<int, int>> getMoves() override;
	void moveTo(int row, int col) override;
};

#endif
