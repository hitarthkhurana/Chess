#include <iostream>
#include "gamemanager.h"
#include "chessboard1v1.h"

GameManager::GameManager() :
    window(make_shared<Xwindow>()),
    board(make_shared<ChessBoard1V1>(window)),
    setupMode(false), gameActive(false) {}

void GameManager::startGame(const string& whitePlayer, const string& blackPlayer) {
    if (whitePlayer == "human") {
        board->setPlayer(1, make_shared<Human>(board, Player::WHITE));
    } else if (whitePlayer == "computer") {
        board->setPlayer(1, make_shared<Computer>(board, Player::WHITE, 1));
    }
    
    if (blackPlayer == "human") {
        board->setPlayer(2, make_shared<Human>(board, Player::BLACK));
    } else if (blackPlayer == "computer") {
        board->setPlayer(2, make_shared<Computer>(board, Player::BLACK, 1));
    }
    
    cout << "Starting game between " << whitePlayer << " and " << blackPlayer << endl;
    board->reset(); // Reset the board for a new game
    setupMode = false;
}

void GameManager::resign() {
    if (gameActive) {
        setupMode = false;
        //cout << (player1->isBlack() ? "White wins!" : "Black wins!") << endl;
    } else {
        cout << "No game in progress to resign from." << endl;
    }
}

void GameManager::processMove(const string& moveCommand) {
    istringstream iss(moveCommand);
    string start, end, promotion;
    iss >> start >> end >> promotion;
    
    cout << "Moved from " << start << " to " << endl;
    if (!promotion.empty()) {
        cout << " and the pawn is promoted to " << promotion;
    }
    cout << endl;
}

void GameManager::enterSetupMode() {
    if (gameActive) {
        cout << "Cannot enter setup mode during an active game." << endl;
    } else {
        setupMode = true;
        cout << "Entered setup mode." << endl;
    }
}

void GameManager::placePiece(const string& piece, const string& position) {
    if (setupMode) {
        board->placePiece(piece, position);
        cout << "Placed " << piece << " at " << position << "." << endl;
    } else {
        cout << "Not in setup mode." << endl;
    }
}

void GameManager::removePiece(const string& position) {
    if (setupMode) {
        board->removePiece(position);
        cout << "Removed piece from " << position << "." << endl;
    } else {
        cout << "Not in setup mode." << endl;
    }
}

void GameManager::setTurn(const string& color) {
    if (setupMode) {
        board->setTurn(color); // Implement this method in ChessBoard
        cout << color << "'s turn next." << endl;
    } else {
        cout << "Not in setup mode." << endl;
    }
}

void GameManager::doneSetup() {
    if (setupMode) {
        // Validate board state
        if (board->hasValidSetup()) {
            setupMode = false;
            cout << "Setup complete." << endl;
        } else {
            cout << "Invalid setup. Make sure there is exactly one white and one black king, no pawns on the first/last row, and no king is in check." << endl;
        }
    } else {
        cout << "Not in setup mode." << endl;
    }
}

void GameManager::processCommand(const string& command) {
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
