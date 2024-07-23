#ifndef CHESSCELL_H
#define CHESSCELL_H
#include <utility>
#include <memory>
#include "displayable.h"
#include "chessboard.h"

class ChessBoard;

class ChessCell : public Displayable {
private:
	bool highlighted;
	std::pair<int, int> chessPos;
	int color;
	
public:
	enum Colors {
		LIGHT = 0, DARK
	};
	ChessCell(shared_ptr<ChessBoard> board, int color);
	void display() override;
	void print() override;
};

#endif
