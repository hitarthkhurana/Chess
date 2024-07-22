#ifndef CHESSBOARD1V1_H
#define CHESSBOARD1V1_H
#include "chessboard.h"
#include "player.h"

class ChessBoard1V1 : public ChessBoard {
public:
	ChessBoard1V1();
	void display() override;
	void print() override;
};

#endif