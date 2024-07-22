#ifndef QUEEN_H
#define QUEEN_H
#include "chesspiece.h"

class Queen : public ChessPiece {
public:
	void display() override;
	void print() override;
};

#endif