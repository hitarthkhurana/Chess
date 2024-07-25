#include <iostream>
#include <cctype>
#include "gamemanager.h"
#include "chessboard1v1.h"
#include "computer.h"

const int WINDOW_SIZE = 720;
const int WHITE_TURN = 1, BLACK_TURN = 2;

GameManager::GameManager() :
    window(make_shared<Xwindow>(WINDOW_SIZE, WINDOW_SIZE)),
    board(make_shared<ChessBoard1V1>(window)),
    setupMode(false), gameActive(false),
	white_wins(0), black_wins(0) {
	
	board->display();
}

void GameManager::startGame(const string& whitePlayer, const string& blackPlayer) {
	if (gameActive) {
		cout << "A game is already in progress." << endl;
	} else {
		board->setPlayer(WHITE_TURN, Player::fromString(whitePlayer, board, Player::WHITE));
		board->setPlayer(BLACK_TURN, Player::fromString(blackPlayer, board, Player::BLACK));
		
		cout << "Starting game between " << whitePlayer << " and " << blackPlayer << "." << endl;
		gameActive = true;
		board->print();
		board->display();
		makeComputerMoves();
	}
}

void GameManager::resign() {
    if (gameActive) {
		if (board->getCurrentPlayer()->getColor() == Player::BLACK) {
			cout << "White wins!" << endl;
			white_wins++;
		} else {
			cout << "Black wins!" << endl;
			black_wins++;
		}
		gameActive = false;
		board->reset();
    } else {
        cout << "No game in progress to resign from." << endl;
    }
}

void GameManager::checkBoardState() {
	int state = board->getState();
	if (state == ChessBoard1V1::CHECK) {
		if (board->getCurrentPlayer()->getColor() == Player::WHITE) {
			cout << "White is in check." << endl;
		} else {
			cout << "Black is in check." << endl;
		}
	} else if (state == ChessBoard1V1::CHECKMATE) {
		cout << "Checkmate! ";
		resign();
	} else if (state == ChessBoard1V1::STALEMATE) {
		cout << "Stalemate!" << endl;
		gameActive = false;
		board->reset();
	}
}

void GameManager::printLastMove() { 
	auto move = board->getLastMove();
	int sz = move.size();
	cout << endl << "Moved ";
	for (int i = 0; i < sz; i += MOVE_SIZE) {
		if (i != 0) {
			cout << " and ";
		}
		cout << "from ";
		cout << static_cast<char>(move[i + 1] + 'a') << (move[i + 0] + 1);
		cout << " to ";
		cout << static_cast<char>(move[i + 3] + 'a') << (move[i + 2] + 1);
	}
	// board->...promotion...();
	cout << "." << endl;
}

void GameManager::makeComputerMoves() {
	while (true) {
		auto computer = dynamic_pointer_cast<Computer>(board->getCurrentPlayer());
		if (!computer) {
			break;
		}
		cout << endl;
		board->makeComputerMove();
		board->display();
		board->print();
		cout << endl;
		printLastMove();
		checkBoardState();
	}
}

void GameManager::processMove(const string& moveCommand) {
	if (gameActive) {
		istringstream iss(moveCommand);
		string start, end, promotion;
		iss >> start >> end >> promotion;

		bool valid = board->move(start, end, promotion);

		if (valid) {
			board->print();
			board->display();
			printLastMove();
			checkBoardState();
			makeComputerMoves();
		} else {
			cout << "Invalid move." << endl;
		}
	} else {
		cout << "Please start a game to perform a move." << endl;
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

void GameManager::displayScore() {
	cout << "Final score:" << endl;
	cout << "White: " << white_wins << endl;
	cout << "Black: " << black_wins << endl;
}

void GameManager::processCommand(const string& command) {
    istringstream iss(command);
    string cmd;
    iss >> cmd;

	for (char &c : cmd) {
		c = tolower(c);
	}

	if (cmd.empty()) {
		return;
	} else if (cmd == "game") {
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
