#ifndef SCORE_H
#define SCORE_H
#include <memory>
#include "displayable.h"
#include "player.h"

class Score : public Displayable {
private:
	std::shared_ptr<Player> player;
	
public:
	void display() override;	
	void print() override;	
};

#endif
