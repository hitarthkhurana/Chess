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
class ChessCell;
class Player;

class ChessBoard : public Displayable, public enable_shared_from_this<ChessBoard> {
protected:
	int moveCnt;
	vector<shared_ptr<Player>> players;
	vector<vector<unique_ptr<ChessCell>>> cells;
	vector<vector<shared_ptr<ChessPiece>>> pieces;
	
public:
	ChessBoard(shared_ptr<Xwindow> window, int player_cnt, int size);
	void reset();
	virtual bool validPos(int row, int col) = 0;
	shared_ptr<ChessPiece> getPiece(int row, int col);
	void setPlayer(int index, shared_ptr<Player> player);
	void placePiece(shared_ptr<ChessPiece> piece, int r, int c);
	void placePiece(const string &piece, const string &position);
	void removePiece(const string &position) {}
	void setTurn(const string &color) {}
	bool hasValidSetup() {return 0;}
	void move(int r1, int c1, int r2, int c2);
	void move(const string &from, const string &to, const string &promotion);
};

#endif
