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
	int color, x, y, size;
	
public:
	enum Colors {
		LIGHT = 0, DARK
	};
	ChessCell(shared_ptr<ChessBoard> board, int color, int x, int y, int size);
	void display() override;
	void print() override;
};

#endif
