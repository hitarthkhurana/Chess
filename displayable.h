#ifndef DISPLAYABLE_H
#define DISPLAYABLE_H
#include <utility>
#include <memory>
#include "xwindow.h"

using namespace std;

class Displayable {
protected:
	shared_ptr<Xwindow> window;
	
public:
	Displayable(shared_ptr<Xwindow> window);
	virtual void display() = 0;
	virtual void print() = 0;
};

#endif
