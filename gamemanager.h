#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "player.h"
#include "human.h"
#include "computer.h"
#include "score.h"
#include "chessboard.h"
#include "xwindow.h"
#include <memory>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class GameManager {
private:
    shared_ptr<Xwindow> window;
    //Score score;
    shared_ptr<ChessBoard> board;
    bool setupMode, gameActive;

public:
    GameManager();

    void startGame(const string& whitePlayer, const string& blackPlayer);
    void resign();
    void processMove(const string& moveCommand);
    void enterSetupMode();
    void placePiece(const string& piece, const string& position);
    void removePiece(const string& position);
    void setTurn(const string& color);
    void doneSetup();
    void processCommand(const string& command);
};

#endif // GAMEMANAGER_H
