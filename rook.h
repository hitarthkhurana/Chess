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

protected:
	const char WHITE_CHAR = 'R', BLACK_CHAR = 'r';

public:
	Rook(shared_ptr<ChessBoard>, int row, int col, int color);
	void display() override;
	void print() override;
	vector<pair<int, int>> getMoves() override;
	void moveTo(int row, int col) override;
};

#endif
