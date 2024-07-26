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
#include "move.h"

using namespace std;

const int ROW_START = '1', COL_START = 'a';

class ChessPiece;
class ChessCell;
class Player;

class ChessBoard : public Displayable, public enable_shared_from_this<ChessBoard> {
protected:
	int moveCnt, state;
	vector<shared_ptr<Player>> players;
	vector<vector<unique_ptr<ChessCell>>> cells;
	vector<vector<shared_ptr<ChessPiece>>> pieces;
	vector<vector<bool>> updated;
	stack<Move> all_moves;
	stack<shared_ptr<ChessPiece>> removed_pieces;
	void setPiece(int row, int col, shared_ptr<ChessPiece> piece);
	virtual void updateState() = 0;
	
public:
	ChessBoard(shared_ptr<Xwindow> window, int player_cnt, int size, int state);
	virtual void reset() = 0;
	virtual void clear() = 0;
	virtual bool validPos(int row, int col) = 0;
	shared_ptr<ChessPiece> getPiece(int row, int col);
	void setPlayer(int index, shared_ptr<Player> player);
	shared_ptr<Player> getPlayer(int index);
	void placePiece(shared_ptr<ChessPiece> piece, int row, int col);
	void removePiece(int row, int col);
	void setTurn(int color);
	virtual bool hasValidSetup() = 0;
	bool doesMoveSelfCheck(const Move &move);
	int tryMove(int r1, int c1, int r2, int c2, int promotion);
	shared_ptr<Player> getCurrentPlayer();
	bool undo(bool stateUpdate = true);
	virtual pair<int, int> getCoords(int row, int col) = 0;
	void processMove(const Move &move, bool stateUpdate = true);
	void makeComputerMove();
	Move getLastMove();
	int getState();

	enum MoveError {
		NONE = 0, BAD_TURN, SELF_CHECK, BAD_PROMOTION, OTHER
	};

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
