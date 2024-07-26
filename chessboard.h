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
	vector<vector<bool>> updated; // Cells that have been updated since last display

	// Store moves and removed pieces in a stack for undoing
	stack<Move> all_moves;
	stack<shared_ptr<ChessPiece>> removed_pieces;

	void setPiece(int row, int col, shared_ptr<ChessPiece> piece);
	virtual void updateState() = 0;
	
public:
	ChessBoard(shared_ptr<Xwindow> window, int player_cnt, int size, int state);
	virtual void reset() = 0; // Reset the board to default configuration
	virtual void clear() = 0; // Clear the board
	virtual bool validPos(int row, int col) = 0;
	shared_ptr<ChessPiece> getPiece(int row, int col) const;
	void setPlayer(int index, shared_ptr<Player> player);
	shared_ptr<Player> getPlayer(int index) const;
	void placePiece(shared_ptr<ChessPiece> piece, int row, int col);
	void removePiece(int row, int col);
	void setTurn(int color);
	virtual bool hasValidSetup() = 0; // Check if the board has a suitable setup
	bool doesMoveSelfCheck(const Move &move);
	int tryMove(int r1, int c1, int r2, int c2, int promotion); // Attempt a move
	shared_ptr<Player> getCurrentPlayer() const;
	bool undo(bool stateUpdate = true); // Undo the last move
	virtual pair<int, int> getCoords(int row, int col) const = 0; // Get x, y positions from row, col
	void processMove(const Move &move, bool stateUpdate = true);
	void makeComputerMove(); // Make one computer move
	Move getLastMove() const; // Return the last move made
	int getState() const; // Return the state of the board

	// Describe the type of error from attempting a move
	enum MoveError {
		NONE = 0, BAD_TURN, SELF_CHECK, BAD_PROMOTION, OTHER
	};

	// Iterate over all pieces in the board
	class Iterator {
	private:
		friend class ChessBoard;
		shared_ptr<ChessBoard> board;
		int i, j;
		Iterator(shared_ptr<ChessBoard> board, int i, int j);
	
	public:
		Iterator& operator++();
		shared_ptr<ChessPiece> operator*() const;
		bool operator==(const Iterator &other) const;
	};

	Iterator begin();
	Iterator end();
};

#endif
