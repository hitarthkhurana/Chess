#ifndef CHESSBOARD1V1_H
#define CHESSBOARD1V1_H
#include <memory>
#include "xwindow.h"
#include "chessboard.h"
#include "player.h"

class ChessBoard1V1 : public ChessBoard {
private:
	bool hasInit;
public:
	ChessBoard1V1(shared_ptr<Xwindow> window);
	void init(); // cannot run "shared_from_this()" in constructor
	void reset() override;
	void display() override;
	void print() override;
	bool validPos(int row, int col) override;
	pair<int, int> getCoords(int row, int col) override;
};

#endif
