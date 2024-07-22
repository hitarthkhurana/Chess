#ifndef CHESSPIECE_H
#define CHESSPIECE_H
#include <vector>
#include <utility>
#include "displayable.h"

class ChessPiece : public Displayable {
protected:
	std::vector<std::pair<int, int>> moves;
	std::pair<int, int> chessPos;
};

#endif