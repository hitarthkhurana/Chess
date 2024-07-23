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
	bool moved;

public:
	static const char WHITE_CHAR = 'R', BLACK_CHAR = 'r';
	Rook(shared_ptr<ChessBoard>, int row, int col, int color);
	void display() override;
	vector<vector<int>> getMoves() override;
	void setPos(int row, int col) override;
	bool hasMoved();
};

#endif
