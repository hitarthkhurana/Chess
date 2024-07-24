#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include <vector>
#include <stack>
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
	stack<vector<int>> all_moves;
	stack<shared_ptr<ChessPiece>> removed_pieces;
	
public:
	ChessBoard(shared_ptr<Xwindow> window, int player_cnt, int size);
	virtual void reset() = 0;
	virtual bool validPos(int row, int col) = 0;
	shared_ptr<ChessPiece> getPiece(int row, int col);
	void setPlayer(int index, shared_ptr<Player> player);
	void placePiece(const string &piece, const string &pos);
	void removePiece(const string &pos);
	bool setTurn(const string &color);
	bool hasValidSetup();
	bool move(const string &from, const string &to, const string &promotion);
	shared_ptr<Player> getCurrentPlayer();
	bool undo();
	virtual pair<int, int> getCoords(int row, int col) = 0;
};

#endif
