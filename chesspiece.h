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
	vector<vector<int>> offsetMoves(const vector<pair<int, int>> &offsets);
	vector<vector<int>> dirMoves(const vector<pair<int, int>> &dirs);
	weak_ptr<ChessBoard> board;
	int row, col, color;
	char white_char, black_char; // use static member instead?

public:
	static shared_ptr<ChessPiece> fromString(const string &s, shared_ptr<ChessBoard> board, int row = -1, int col = -1);
	ChessPiece(shared_ptr<ChessBoard>, int row, int col, int color, char white_car, char black_char);
	virtual vector<vector<int>> getMoves() = 0;
	virtual void setPos(int row, int col);
	void print() override;
	int getColor();
};

#endif
