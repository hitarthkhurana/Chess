#ifndef QUEEN_H
#define QUEEN_H
#include <memory>
#include <vector>
#include <utility>
#include "chesspiece.h"
#include "chessboard.h"

using namespace std;

class Queen : public ChessPiece {
public:
	static const char WHITE_CHAR = 'Q', BLACK_CHAR = 'q';
	Queen(shared_ptr<ChessBoard>, int row, int col, int color);
	vector<vector<int>> getMoves() override;
};

#endif
