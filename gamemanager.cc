#include <iostream>
#include <cctype>
#include <set>
#include "gamemanager.h"
#include "chessboard1v1.h"
#include "computer.h"
#include "move.h"

const int WINDOW_SIZE = 720, POS_SIZE = 2;
const int WHITE_TURN = 1, BLACK_TURN = 2;
const set<string> VALID_PLAYERS = {"human", "computer1", "computer2", "computer3", "computer4", "computer5"};

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
	} else if (setupMode) {
		cout << "You must leave setup mode to start a game." << endl;
	} else if (!VALID_PLAYERS.count(whitePlayer) || !VALID_PLAYERS.count(blackPlayer)) {
		cout << "Both player must be specified as either 'human' or 'computer[1-5]'." << endl;
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

void GameManager::printLastMove() const { 
	auto move = board->getLastMove();
	cout << endl << "Moved from ";
	cout << static_cast<char>(move.c1 + COL_START);
	cout << static_cast<char>(move.r1 + ROW_START);
	cout << " to ";
	cout << static_cast<char>(move.c2 + COL_START);
	cout << static_cast<char>(move.r2 + ROW_START);
	if (move.castle) {
		cout << " and from ";
		cout << static_cast<char>(move.c3 + COL_START);
		cout << static_cast<char>(move.r3 + ROW_START);
		cout << " to ";
		cout << static_cast<char>(move.c4 + COL_START);
		cout << static_cast<char>(move.r4 + ROW_START);
	} else if (move.promotion != Move::NONE) {
		cout << " and promoted pawn to ";
		if (move.promotion == Move::QUEEN) {
			cout << "queen";
		} else if (move.promotion == Move::ROOK) {
			cout << "rook";
		} else if (move.promotion == Move::BISHOP) {
			cout << "bishop";
		} else {
			cout << "knight";
		}
	}
	cout << "." << endl;
}

void GameManager::makeComputerMoves() {
	while (gameActive) {
		if (!dynamic_pointer_cast<Computer>(board->getCurrentPlayer())) {
			break;
		}
		cout << endl << "Computer's turn..." << endl << endl;
		board->makeComputerMove();
		board->display();
		board->print();
		printLastMove();
		checkBoardState();
	}
}

void GameManager::processMove(const string& from, const string& to, const string& promotion) {
	if (gameActive) {
		int row1 = from[1] - ROW_START, col1 = from[0] - COL_START;
		int row2 = to[1] - ROW_START, col2 = to[0] - COL_START;
		if (from.size() != POS_SIZE || !board->validPos(row1, col1)) {
			cout << "Invalid starting position." << endl;
			return;
		} else if (to.size() != POS_SIZE || !board->validPos(row2, col2)) {
			cout << "Invalid ending position." << endl;
			return;
		}

		int promotion2;
		if (promotion.empty()) {
			promotion2 = Move::NONE;
		} else if (promotion == "q") {
			promotion2 = Move::QUEEN;
		} else if (promotion == "r") {
			promotion2 = Move::ROOK;
		} else if (promotion == "b") {
			promotion2 = Move::BISHOP;
		} else if (promotion == "n") {
			promotion2 = Move::KNIGHT;
		} else {
			cout << "Invalid promotion." << endl;
			return;
		}

		int result = board->tryMove(row1, col1, row2, col2, promotion2);

		if (result == ChessBoard::BAD_TURN) {
			cout << "Please move your own piece." << endl;
		} else if (result == ChessBoard::SELF_CHECK) {
			cout << "You cannot move yourself into check." << endl;
		} else if (result == ChessBoard::BAD_PROMOTION) {
			cout << "Invalid promotion." << endl;
		} else if (result == ChessBoard::OTHER) {
			cout << "Invalid Move" << endl;
		} else {
			board->print();
			board->display();
			humanMoveCnt++;
			printLastMove();
			checkBoardState();
			makeComputerMoves();
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
		board->clear();
		board->display();
        cout << "Entered setup mode." << endl;
    }
}

void GameManager::placePiece(const string& piece, const string& pos) {
    if (setupMode) {
		int row = pos[1] - ROW_START, col = pos[0] - COL_START;
		auto piece2 = ChessPiece::fromString(piece, board, row, col);
		if (pos.size() != POS_SIZE || !board->validPos(row, col)) {
			cout << "Invalid position." << endl;
		} else if (!piece2) {
			cout << "Invalid piece." << endl;
		} else {
			board->placePiece(piece2, row, col);
			board->print();
			board->display();
			cout << endl << "Placed " << piece << " at " << pos << "." << endl;
		}
    } else {
        cout << "Not currently in setup mode." << endl;
    }
}

void GameManager::removePiece(const string& pos) {
    if (setupMode) {
		int row = pos[1] - ROW_START, col = pos[0] - COL_START;
		if (pos.size() != POS_SIZE || !board->validPos(row, col)) {
			cout << "Invalid position." << endl;
		} else {
			board->removePiece(row, col);
			board->print();
			board->display();
			cout << endl << "Removed piece from " << pos << "." << endl;
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
		board->undo();
		while (dynamic_pointer_cast<Computer>(board->getCurrentPlayer())) {
			board->undo();
		}
		board->print();
		board->display();
		humanMoveCnt--;
		cout << endl << "Undo successful." << endl;
	}
}

void GameManager::printScore() const {
	cout << "Final score:" << endl;
	cout << "White: " << whiteWins << endl;
	cout << "Black: " << blackWins << endl;
}

void GameManager::printHelp() const {
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

bool GameManager::processCommand(const string& command) {
    istringstream iss(command);
    string cmd;
    iss >> cmd;
	cmd = tolower(cmd);

	if (cmd.empty()) {
		return true;
	} else if (cmd == "game") {
        string whitePlayer, blackPlayer;
        iss >> whitePlayer >> blackPlayer;
        startGame(tolower(whitePlayer), tolower(blackPlayer));
    } else if (cmd == "resign") {
        resign();
    } else if (cmd == "move") {
        string from, to, promotion;
		iss >> from >> to >> promotion;
        processMove(tolower(from), tolower(to), tolower(promotion));
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
		return false;
    } else {
        cout << "Unknown command." << endl;
		cout << "Enter 'help' for a full list of commands." << endl;
    }
	return true;
}
