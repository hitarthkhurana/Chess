#ifndef CHESSPIECE_H
#define CHESSPIECE_H
#include <vector>
#include <utility>
#include <memory>
#include "displayable.h"
#include "chessboard.h"

using namespace std;

class ChessBoard;

class ChessPiece : public Displayable {
protected:
	const char WHITE_CHAR, BLACK_CHAR;
	vector<pair<int, int>> offsetMoves(vector<pair<int, int>> &offsets);
	vector<pair<int, int>> dirMoves(vector<pair<int, int>> &dirs);
	shared_ptr<ChessBoard> board;
	int row, col, color;

public:
	ChessPiece(shared_ptr<ChessBoard>, int row, int col, int color);
	virtual vector<pair<int, int>> getMoves() = 0;
	virtual void moveTo(int row, int col);
	void print() override;
};

#endif
