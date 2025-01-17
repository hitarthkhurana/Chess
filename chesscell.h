#ifndef CHESSCELL_H
#define CHESSCELL_H
#include <utility>
#include <memory>
#include "displayable.h"
#include "chessboard.h"

class ChessBoard;

class ChessCell : public Displayable {
private:
	weak_ptr<ChessBoard> board; // Keep track of the board
	int row, col, color, size;  // Chess cell attributes
	
public:
	// Color of chess cell
	enum Colors {
		LIGHT = 0, DARK
	};

	ChessCell(shared_ptr<ChessBoard> board, int row, int col, int color, int size);
	void display() override;
	void print() override;
};

#endif
