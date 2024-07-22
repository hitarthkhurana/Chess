#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include <vector>
#include <memory>
#include "xwindow.h"
#include "displayable.h"
#include "chesscell.h"
#include "chesspiece.h"
#include "player.h"

using namespace std;

class ChessPiece;
class Player;

class ChessBoard : public Displayable {
protected:
	int moveCnt;
	vector<shared_ptr<Player>> players;
	vector<vector<unique_ptr<ChessCell>>> cells;
	vector<vector<shared_ptr<ChessPiece>>> pieces;
	
public:
	ChessBoard(shared_ptr<Xwindow> window);
	void reset();
	virtual bool validPos(int row, int col) = 0;
	shared_ptr<ChessPiece> getPiece(int row, int col);
};

#endif
