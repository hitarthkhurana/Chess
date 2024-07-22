#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <memory>
#include "score.h"
#include "chessboard.h"

class GameManager {
private:
	std::shared_ptr<ChessBoard> board;
	
public:
	GameManager();
	void start();
};

#endif