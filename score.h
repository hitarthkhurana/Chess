#ifndef SCORE_H
#define SCORE_H
#include <memory>
#include "displayable.h"
#include "player.h"
#include "xwindow.h"

class Score : public Displayable {
private:
	std::shared_ptr<Player> player;
	
public:
	//Score(std::shared_ptr<Player> player); // not correct
	Score(shared_ptr<Xwindow> window) : Displayable(window) {}
	void display() override;	
	void print() override;	
};

#endif
