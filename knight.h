#ifndef KNIGHT_H
#define KNIGHT_H
#include <memory>
#include <vector>
#include <utility>
#include "chesspiece.h"
#include "chessboard.h"

using namespace std;

class Knight : public ChessPiece {
public:
	static const char WHITE_CHAR = 'N', BLACK_CHAR = 'n';
	Knight(shared_ptr<ChessBoard>, int row, int col, int color);
	void display() override;
	vector<pair<int, int>> getMoves() override;
};

#endif
