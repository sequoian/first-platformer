#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

#include "PlayerState.h"

class Global : public PlayerState {
public:
	void enter(Hero& hero);
	void exit(Hero& hero);
	void handleInput(Hero& hero, const InputData& data);
	void update(Hero& hero);
};

#endif