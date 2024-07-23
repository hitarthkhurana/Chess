#include <iostream>
#include "chesscell.h"
#include "xwindow.h"

using namespace std;

const char EMPTY_LIGHT = ' ';
const char EMPTY_DARK = '_';

ChessCell::ChessCell(shared_ptr<ChessBoard> board, int color, int x, int y, int size) :
	Displayable(board->getWindow()), color(color), x(x), y(y), size(size) {}

void ChessCell::display() {
	window->fillRectangle(x, y, size, size,
		color == LIGHT ? Xwindow::White : Xwindow::Black);
}

void ChessCell::print() {
	if (color == LIGHT) {
		cout << EMPTY_LIGHT;
	} else {
		cout << EMPTY_DARK;
	}
}
