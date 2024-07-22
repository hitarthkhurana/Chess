#include <iostream>
#include "chesscell.h"

using namespace std;

const char EMPTY_LIGHT = ' ';
const char EMPTY_DARK = '_';

ChessCell::ChessCell(int color) : color(color) {}

void ChessCell::display() {

}

void ChessCell::print() {
	if (color == LIGHT) {
		cout << EMPTY_LIGHT;
	} else {
		cout << EMPTY_DARK;
	}
}
