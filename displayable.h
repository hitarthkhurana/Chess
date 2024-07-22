#ifndef DISPLAYABLE_H
#define DISPLAYABLE_H
#include <utility>

class Displayable {
private:
	std::pair<int, int> pos;
	
public:
	virtual void display() = 0;
	virtual void print() = 0;	
};

#endif