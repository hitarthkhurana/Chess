#include "displayable.h"

using namespace std;

Displayable::Displayable(shared_ptr<Xwindow> window) : 
	window(window) {}

shared_ptr<Xwindow> Displayable::getWindow() const {
	return window;
}
