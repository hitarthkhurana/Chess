#include <iostream>
#include <cctype>
#include "gamemanager.h"
#include "chessboard1v1.h"

const int WINDOW_SIZE = 800;

GameManager::GameManager() :
    window(make_shared<Xwindow>(WINDOW_SIZE, WINDOW_SIZE)),
    board(make_shared<ChessBoard1V1>(window)),
    setupMode(false), gameActive(false) {}

void GameManager::startGame(const string& whitePlayer, const string& blackPlayer) {
	board->setPlayer(1, Player::fromString(whitePlayer, board, Player::WHITE));
	board->setPlayer(2, Player::fromString(blackPlayer, board, Player::BLACK));
    
    cout << "Starting game between " << whitePlayer << " and " << blackPlayer << "." << endl;
	gameActive = true;
	board->print();
	board->display();
}

void GameManager::resign() {
    if (gameActive) {
		if (board->getCurrentPlayer()->getColor() == Player::BLACK) {
			cout << "White wins!" << endl;
		} else {
			cout << "Black wins!" << endl;
		}
		gameActive = false;
		board->reset();
    } else {
        cout << "No game in progress to resign from." << endl;
    }
}

void GameManager::processMove(const string& moveCommand) {
    istringstream iss(moveCommand);
    string start, end, promotion;
    iss >> start >> end >> promotion;

    bool valid = board->move(start, end, promotion);

	if (valid) {
		cout << "Moved from " << start << " to " << end;
		if (!promotion.empty()) {
			cout << " and the pawn is promoted to " << promotion;
		}
		cout << "." << endl;
		board->print();
		board->display();
	} else {
		cout << "Invalid move." << endl;
	}
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
		board->print();
		board->display();
        cout << "Placed " << piece << " at " << position << "." << endl;
    } else {
        cout << "Not currently in setup mode." << endl;
    }
}

void GameManager::removePiece(const string& position) {
    if (setupMode) {
        board->removePiece(position);
		board->print();
		board->display();
        cout << "Removed piece from " << position << "." << endl;
    } else {
        cout << "Not currently in setup mode." << endl;
    }
}

void GameManager::setTurn(const string& color) {
    if (setupMode) {
        bool success = board->setTurn(color);
		if (!success) {
			cout << "Invalid color." << endl;
		} else {
			cout << color << " will go first." << endl;
		}
    } else {
        cout << "Not currently in setup mode." << endl;
    }
}

void GameManager::doneSetup() {
    if (setupMode) {
        // Validate board state
        if (board->hasValidSetup()) {
            setupMode = false;
            cout << "Setup complete." << endl;
        } else {
            cout << "Invalid setup." << endl;
			cout << "Make sure there is exactly one white and one black king." << endl;
			cout << "Make sure no pawns are on the first/last row, and no king is in check." << endl;
        }
    } else {
        cout << "Not currently in setup mode." << endl;
    }
}

void GameManager::undoMove() {
	if (!gameActive) {
		cout << "No game in progress." << endl;
	} else {
		bool success = board->undo();
		if (success) {
			cout << "Undid last move." << endl;
			board->print();
			board->display();
		} else {
			cout << "No moves to undo." << endl;
		}
	}
}

void GameManager::processCommand(const string& command) {
    istringstream iss(command);
    string cmd;
    iss >> cmd;

	for (char &c : cmd) {
		c = tolower(c);
	}

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
	} else if (cmd == "undo") {
		undoMove();
	} else if (cmd == "exit" || cmd == "quit") {
		cout << "Bye!" << endl;
		exit(0);
    } else {
        cout << "Unknown command." << endl;
    }
}
