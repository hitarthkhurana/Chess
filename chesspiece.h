#ifndef CHESSPIECE_H
#define CHESSPIECE_H
#include <vector>
#include <utility>
#include <memory>
#include "displayable.h"
#include "chessboard.h"
#include "move.h"

using namespace std;

class ChessBoard;

class ChessPiece : public Displayable {
protected:
	// Get a list of moves based on offsets or directions
	vector<Move> offsetMoves(const vector<pair<int, int>> &offsets) const;
	vector<Move> dirMoves(const vector<pair<int, int>> &dirs) const;

	weak_ptr<ChessBoard> board; // Keep track of the board

	// Chess piece attributes
	int row, col, color;
	char white_char, black_char;

public:
	// Create a ChessPiece from a string or promotion (int)
	static shared_ptr<ChessPiece> fromString(const string &s, shared_ptr<ChessBoard> board, int row, int col);
	static shared_ptr<ChessPiece> fromPromotion(int promotion, shared_ptr<ChessBoard> board, int row, int col, int color);

	ChessPiece(shared_ptr<ChessBoard> board, int row, int col, int color, char white_char, char black_char);
	virtual vector<Move> getMoves() const = 0;
	virtual void setPos(int row, int col, bool undo = false);
	void print() override;
	void display() override;
	int getColor() const;
	pair<int, int> getPos() const;
};

#endif
