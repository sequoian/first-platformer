#ifndef DEAD_H_INCLUDED
#define DEAD_H_INCLUDED

#include "PlayerState.h"

class Dead : public PlayerState{
public:
	void enter(Hero& hero);
	void exit(Hero& hero);
	void handleInput(Hero& hero, const InputData& data);
	void update(Hero& hero);
private:
	bool done_;

};

#endif