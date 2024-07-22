#ifndef CHESSCELL_H
#define CHESSCELL_H
#include <utility>
#include "displayable.h"

class ChessCell : public Displayable {
private:
	bool highlighted;
	std::pair<int, int> chessPos;
	bool black;
	
public:
	void display() override;
	void print() override;
};

#endif