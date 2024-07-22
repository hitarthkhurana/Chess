#ifndef BISHOP_H
#define BISHOP_H
#include "chesspiece.h"

class Bishop : public ChessPiece {
public:
	void display() override;
	void print() override;
};

#endif
