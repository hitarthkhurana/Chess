#include <iostream>
#include "chesscell.h"
#include "xwindow.h"

using namespace std;

const char EMPTY_LIGHT = ' ';
const char EMPTY_DARK = '_';

ChessCell::ChessCell(shared_ptr<ChessBoard> board, int row, int col, int color, int size) :
	Displayable(board->getWindow()), board(board), row(row), col(col), color(color), size(size) {}

void ChessCell::display() {
	// Draw a square of the appropriate color onto the needed position
	auto [x, y] = board.lock()->getCoords(row, col);
	window->fillRectangle(x, y, size, size,
		color == LIGHT ? Xwindow::LIGHT_GREEN : Xwindow::DARK_GREEN);
}

void ChessCell::print() {
	// Print a character based on the color of the cell
	if (color == LIGHT) {
		cout << EMPTY_LIGHT;
	} else {
		cout << EMPTY_DARK;
	}
}
