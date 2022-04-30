#ifndef WALKING_H_INCLUDED
#define WALKING_H_INCLUDED

#include "PlayerState.h"

class Walking : public PlayerState{
public:
	void enter(Hero& hero);
	void exit(Hero& hero);
	void handleInput(Hero& hero, const InputData& data);
	void update(Hero& hero);
};

#endif