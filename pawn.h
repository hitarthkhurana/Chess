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
	int moveCnt = 0; // Move count to determine whether pawn can move two forward

public:
	static const char WHITE_CHAR = 'P', BLACK_CHAR = 'p';
	Pawn(shared_ptr<ChessBoard>, int row, int col, int color);
	vector<Move> getMoves() const override;
	void setPos(int row, int col, bool undo) override;
};

#endif
