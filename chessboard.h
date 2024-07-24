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

const int MOVE_SIZE = 4;

class ChessPiece;
class ChessCell;
class Player;

class ChessBoard : public Displayable, public enable_shared_from_this<ChessBoard> {
protected:
	int moveCnt, status;
	vector<shared_ptr<Player>> players;
	vector<vector<unique_ptr<ChessCell>>> cells;
	vector<vector<shared_ptr<ChessPiece>>> pieces;
	vector<vector<bool>> updated;
	stack<vector<int>> all_moves;
	stack<shared_ptr<ChessPiece>> removed_pieces;
	void setPiece(int row, int col, shared_ptr<ChessPiece> piece);
	virtual void updateStatus() = 0;
	
public:
	ChessBoard(shared_ptr<Xwindow> window, int player_cnt, int size);
	virtual void reset() = 0;
	virtual bool validPos(int row, int col) = 0;
	shared_ptr<ChessPiece> getPiece(int row, int col);
	void setPlayer(int index, shared_ptr<Player> player);
	shared_ptr<Player> getPlayer(int index);
	void placePiece(const string &piece, const string &pos);
	void removePiece(const string &pos);
	bool setTurn(const string &color);
	bool hasValidSetup();
	bool move(const string &from, const string &to, const string &promotion);
	shared_ptr<Player> getCurrentPlayer();
	bool undo();
	virtual pair<int, int> getCoords(int row, int col) = 0;
	void processMove(const vector<int> &move);
	void makeComputerMove();
	vector<int> getLastMove();
	int getStatus();

	class Iterator {
	private:
		friend class ChessBoard;
		shared_ptr<ChessBoard> board;
		int i, j;
		Iterator(shared_ptr<ChessBoard> board, int i, int j);
	
	public:
		Iterator& operator++();
		shared_ptr<ChessPiece> operator*();
		bool operator==(const Iterator &other);
	};

	Iterator begin();
	Iterator end();
};

#endif
