#ifndef ROOK_H
#define ROOK_H
#include "chesspiece.h"

class Rook : public ChessPiece {
public:
	void display() override;
	void print() override;
};

#endif