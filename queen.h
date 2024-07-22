#ifndef QUEEN_H
#define QUEEN_H
#include <memory>
#include <vector>
#include <utility>
#include "chesspiece.h"
#include "chessboard.h"

using namespace std;

class Queen : public ChessPiece {
protected:
	const char WHITE_CHAR = 'Q', BLACK_CHAR = 'q';

public:
	Queen(shared_ptr<ChessBoard>, int row, int col, int color);
	void display() override;
	void print() override;
	vector<pair<int, int>> getMoves() override;
};

#endif
