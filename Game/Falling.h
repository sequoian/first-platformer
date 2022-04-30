#ifndef FALLING_H_INCLUDED
#define FALLING_H_INCLUDED

#include "PlayerState.h"

class Falling : public PlayerState{
public:
	void enter(Hero& hero);
	void exit(Hero& hero);
	void handleInput(Hero& hero, const InputData& data);
	void update(Hero& hero);
};

#endif