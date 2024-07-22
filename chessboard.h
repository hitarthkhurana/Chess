#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include <vector>
#include <memory>
#include "displayable.h"
#include "chesscell.h"
#include "chesspiece.h"
#include "player.h"

using namespace std;

class ChessBoard : public Displayable {
protected:
	int moveCnt;
	vector<shared_ptr<Player>> players;
	vector<unique_ptr<ChessCell>> cells;
	vector<unique_ptr<ChessPiece>> pieces;
	
public:
	void reset();
};

#endif