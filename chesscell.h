#ifndef CHESSCELL_H
#define CHESSCELL_H
#include <utility>
#include "displayable.h"

class ChessCell : public Displayable {
private:
	bool highlighted;
	std::pair<int, int> chessPos;
	int color;
	
public:
	enum Colors {
		LIGHT = 0, DARK
	};
	ChessCell(int color);
	void display() override;
	void print() override;
};

#endif
