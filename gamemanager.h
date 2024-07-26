#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <memory>
#include <string>
#include <vector>
#include <sstream>
#include "player.h"
#include "human.h"
#include "computer.h"
#include "chessboard.h"
#include "xwindow.h"

using namespace std;

class GameManager {
private:
    shared_ptr<Xwindow> window;
    shared_ptr<ChessBoard> board;
    bool setupMode, gameActive;
	int whiteWins, blackWins, humanMoveCnt;

public:
    GameManager();

    void startGame(const string& whitePlayer, const string& blackPlayer);
    void resign();
    void checkBoardState();
    void processMove(const string& from, const string& to, const string &promotion);
    void printLastMove() const;
    void makeComputerMoves();
    void enterSetupMode();
    void placePiece(const string& piece, const string& pos);
    void removePiece(const string& pos);
    void setTurn(const string& color);
    void doneSetup();
	void undoMove();
	void printScore() const;
	void printHelp() const;
    bool processCommand(const string& command);
};

#endif // GAMEMANAGER_H
