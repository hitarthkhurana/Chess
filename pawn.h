#ifndef PAWN_H
#define PAWN_H
#include <memory>
#include <vector>
#include <utility>
#include "chessboard.h"
#include "chesspiece.h"

using namespace std;

class Pawn : public ChessPiece {
private:
	int moveCnt = 0;

public:
	static const char WHITE_CHAR = 'P', BLACK_CHAR = 'p';
	Pawn(shared_ptr<ChessBoard>, int row, int col, int color);
	vector<Move> getMoves() override;
	void setPos(int row, int col, bool undo) override;
};

#endif
