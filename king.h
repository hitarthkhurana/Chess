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
	int moveCnt;

public:
	static const char WHITE_CHAR = 'K', BLACK_CHAR = 'k';
	King(shared_ptr<ChessBoard>, int row, int col, int color);
	vector<vector<int>> getMoves() override;
	void setPos(int row, int col, bool undo = false) override;
	bool hasMoved();
};

#endif
