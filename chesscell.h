#ifndef CHESSCELL_H
#define CHESSCELL_H
#include <utility>
#include <memory>
#include "displayable.h"
#include "chessboard.h"

class ChessBoard;

class ChessCell : public Displayable {
private:
	weak_ptr<ChessBoard> board;
	bool highlighted;
	std::pair<int, int> chessPos;
	int row, col, color, size;
	
public:
	enum Colors {
		LIGHT = 0, DARK
	};
	ChessCell(shared_ptr<ChessBoard> board, int row, int col, int color, int size);
	void display() override;
	void print() override;
};

#endif
