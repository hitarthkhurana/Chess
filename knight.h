#ifndef KNIGHT_H
#define KNIGHT_H
#include "chesspiece.h"

class Knight : public ChessPiece {
public:
	void display() override;
	void print() override;
};

#endif