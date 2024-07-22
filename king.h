#ifndef KING_H
#define KING_H
#include "chesspiece.h"

class King : public ChessPiece {
public:
	void display() override;
	void print() override;
};

#endif