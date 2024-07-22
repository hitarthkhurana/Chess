#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Player.h"
#include "Human.h"
#include "Computer.h"
#include "Score.h"
#include "ChessBoard.h"
#include <memory>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class GameManager {
    unique_ptr<Displayable> window;
    unique_ptr<Player> player1;
    unique_ptr<Player> player2;
    Score score;
    ChessBoard board;
    bool setupMode = false;
public:
    GameManager() {}

    void startGame(const string& whitePlayer, const string& blackPlayer) {
        if (whitePlayer == "human") player1 = make_unique<Human>();
        else if (whitePlayer == "computer") player1 = make_unique<Computer>();
        
        if (blackPlayer == "human") player2 = make_unique<Human>();
        else if (blackPlayer == "computer") player2 = make_unique<Computer>();

        player1->setBlack(false);
        player2->setBlack(true);
        
        cout << "Starting game between " << whitePlayer << " and " << blackPlayer << endl;
        board.reset(); // Reset the board for a new game
        setupMode = false;
    }

    void resign() {
        if (player1 && player2) {
            setupMode = false;
            cout << (player1->isBlack() ? "White wins!" : "Black wins!") << endl;
        } else {
            cout << "No game in progress to resign from." << endl;
        }
    }

    void processMove(const string& moveCommand) {
        istringstream iss(moveCommand);
        string start, end, promotion;
        iss >> start >> end >> promotion;
        
        cout << "Moved from " << start << " to " << end;
        if (!promotion.empty()) {
            cout << " and the pawn is promoted to " << promotion;
        }
        cout << endl;
    }

    void enterSetupMode() {
        if (player1 && player2) {
            cout << "Cannot enter setup mode during an active game." << endl;
        } else {
            setupMode = true;
            cout << "Entered setup mode." << endl;
        }
    }

    void placePiece(const string& piece, const string& position) {
        if (setupMode) {
            board.placePiece(piece, position);
            cout << "Placed " << piece << " at " << position << "." << endl;
        } else {
            cout << "Not in setup mode." << endl;
        }
    }

    void removePiece(const string& position) {
        if (setupMode) {
            board.removePiece(position);
            cout << "Removed piece from " << position << "." << endl;
        } else {
            cout << "Not in setup mode." << endl;
        }
    }

    void setTurn(const string& color) {
        if (setupMode) {
            board.setTurn(color); // Implement this method in ChessBoard
            cout << color << "'s turn next." << endl;
        } else {
            cout << "Not in setup mode." << endl;
        }
    }

    void doneSetup() {
        if (setupMode) {
            // Validate board state
            if (board.isValidSetup()) {
                setupMode = false;
                cout << "Setup complete." << endl;
            } else {
                cout << "Invalid setup. Make sure there is exactly one white and one black king, no pawns on the first/last row, and no king is in check." << endl;
            }
        } else {
            cout << "Not in setup mode." << endl;
        }
    }

    void processCommand(const string& command) {
        istringstream iss(command);
        string cmd;
        iss >> cmd;

        if (cmd == "game") {
            string whitePlayer, blackPlayer;
            iss >> whitePlayer >> blackPlayer;
            startGame(whitePlayer, blackPlayer);

        } else if (cmd == "resign") {
            resign();

        } else if (cmd == "move") {
            string moveCommand;
            getline(iss, moveCommand);
            processMove(moveCommand);

        } else if (cmd == "setup") {
            enterSetupMode();
        
        } else if (cmd == "+") {
            string piece, position;
            iss >> piece >> position;
            placePiece(piece, position);
        
        } else if (cmd == "-") {
            string position;
            iss >> position;
            removePiece(position);

        } else if (cmd == "=") {
            string color;
            iss >> color;
            setTurn(color);

        } else if (cmd == "done") {
            doneSetup();

        } else {
            cout << "Unknown command." << endl;
        }
    }
};

#endif // GAMEMANAGER_H
