#include <iostream>
#include <cctype>
#include <set>
#include "gamemanager.h"
#include "chessboard1v1.h"
#include "computer.h"

const int WINDOW_SIZE = 720;
const int WHITE_TURN = 1, BLACK_TURN = 2;
const set<string> VALID_PLAYERS = {"human", "computer1", "computer2", "computer3", "computer4"};

string tolower(const string& s) {
	string ans = s;
	for (char c : ans) {
		c = tolower(c);
	}
	return ans;
}

GameManager::GameManager() :
    window(make_shared<Xwindow>(WINDOW_SIZE, WINDOW_SIZE)),
    board(make_shared<ChessBoard1V1>(window)),
    setupMode(false), gameActive(false),
	whiteWins(0), blackWins(0), humanMoveCnt(0) {
	
	board->display();
	board->setPlayer(WHITE_TURN, Player::fromString("human", board, Player::WHITE));
	board->setPlayer(BLACK_TURN, Player::fromString("human", board, Player::BLACK));
}

void GameManager::startGame(const string& whitePlayer, const string& blackPlayer) {
	if (gameActive) {
		cout << "A game is already in progress." << endl;
	} else if (!VALID_PLAYERS.count(whitePlayer) || !VALID_PLAYERS.count(blackPlayer)) {
		cout << "Both player must be specified as either 'human' or 'computer[1-4]'." << endl;
	} else {
		board->setPlayer(WHITE_TURN, Player::fromString(whitePlayer, board, Player::WHITE));
		board->setPlayer(BLACK_TURN, Player::fromString(blackPlayer, board, Player::BLACK));
		
		cout << "Starting game between " << whitePlayer << " and " << blackPlayer << "." << endl << endl;
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
			whiteWins++;
		} else {
			cout << "Black wins!" << endl;
			blackWins++;
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
		cout << static_cast<char>(move[i + 1] + COL_START) << (move[i + 0] + 1);
		cout << " to ";
		cout << static_cast<char>(move[i + 3] + COL_START) << (move[i + 2] + 1);
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

void GameManager::processMove(const string& from, const string& to, const string& promotion) {
	if (gameActive) {
		bool valid = board->move(from, to, promotion);

		if (valid) {
			board->print();
			board->display();
			humanMoveCnt++;
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
        if (board->placePiece(piece, position)) {
			board->print();
			board->display();
			cout << "Placed " << piece << " at " << position << "." << endl;
		} else {
			cout << "Invalid piece or position." << endl;
		}
    } else {
        cout << "Not currently in setup mode." << endl;
    }
}

void GameManager::removePiece(const string& position) {
    if (setupMode) {
		if (board->removePiece(position)) {
			board->print();
			board->display();
			cout << "Removed piece from " << position << "." << endl;
		} else {
			cout << "Invalid position." << endl;
		}
    } else {
        cout << "Not currently in setup mode." << endl;
    }
}

void GameManager::setTurn(const string& color) {
    if (setupMode) {
		if (color == "white") {
			board->setTurn(Player::WHITE);
		} else if (color == "black") {
			board->setTurn(Player::BLACK);
		} else {
			cout << "Invalid color." << endl;
			return;
		}
		cout << static_cast<char>(toupper(color[0])) << color.substr(1);
		cout << " will go first." << endl;
    } else {
        cout << "Not currently in setup mode." << endl;
    }
}

void GameManager::doneSetup() {
    if (setupMode) {
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
	} else if (humanMoveCnt == 0) {
		cout << "No moves to undo." << endl;
	} else {
		while (dynamic_pointer_cast<Computer>(board->getCurrentPlayer())) {
			board->undo();
		}
		board->undo();
		board->print();
		board->display();
		humanMoveCnt--;
		cout << "Undid last move." << endl;
	}
}

void GameManager::printScore() {
	cout << "Final score:" << endl;
	cout << "White: " << whiteWins << endl;
	cout << "Black: " << blackWins << endl;
}

void GameManager::printHelp() {
	cout << "Available commands:" << endl;
	if (setupMode) {
		cout << "  + PIECE POS -- adds the piece PIECE to position POS" << endl;
		cout << "  - POS       -- removes the piece, if any, from position POS" << endl;
		cout << "  = COLOUR    -- makes it COLOUR's turn to go first" << endl;
		cout << "  done        -- leaves setup mode" << endl;
	} else if (gameActive) {
		cout << "  move POS1 POS2 -- moves the piece at POS1 to POS2" << endl;
		cout << "  undo           -- undo moves until a human's turn is reached" << endl;
		cout << "  resign         -- the current player resigns to end the game" << endl;

	} else {
		cout << "  game WHITE BLACK -- starts a new game between WHITE and BLACK" << endl;
		cout << "  setup            -- enters setup mode" << endl;
		cout << "  quit             -- exits the program" << endl;
	}
}

void GameManager::processCommand(const string& command) {
    istringstream iss(command);
    string cmd;
    iss >> cmd;
	cmd = tolower(cmd);

	if (cmd.empty()) {
		return;
	} else if (cmd == "game") {
        string whitePlayer, blackPlayer;
        iss >> whitePlayer >> blackPlayer;
        startGame(tolower(whitePlayer), tolower(blackPlayer));
    } else if (cmd == "resign") {
        resign();
    } else if (cmd == "move") {
        string from, to, promotion;
		iss >> from >> to >> promotion;
        processMove(tolower(from), tolower(to), promotion);
    } else if (cmd == "setup") {
        enterSetupMode();
    } else if (cmd == "+") {
        string piece, position;
        iss >> piece >> position;
        placePiece(piece, tolower(position));
    } else if (cmd == "-") {
        string position;
        iss >> position;
        removePiece(tolower(position));
    } else if (cmd == "=") {
        string color;
        iss >> color;
        setTurn(tolower(color));
    } else if (cmd == "done") {
        doneSetup();
	} else if (cmd == "undo") {
		undoMove();
	} else if (cmd == "score") {
		printScore();
	} else if (cmd == "help") {
		printHelp();
	} else if (cmd == "quit") {
		cout << "Bye!" << endl;
		exit(0);
    } else {
        cout << "Unknown command." << endl;
		cout << "Enter 'help' for a full list of commands." << endl;
    }
}
