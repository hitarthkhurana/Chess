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
	int moveCnt; // Move count to see if castling is allowed

public:
	static const char WHITE_CHAR = 'R', BLACK_CHAR = 'r';
	Rook(shared_ptr<ChessBoard>, int row, int col, int color);
	vector<Move> getMoves() const override;
	void setPos(int row, int col, bool undo = false) override;
	bool hasMoved() const;
};

#endif
