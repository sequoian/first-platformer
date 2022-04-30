#ifndef WALL_CLINGING_H_INCLUDED
#define WALL_CLINGING_H_INCLUDED

#include "PlayerState.h"
#include "Helpers.h"

class WallClinging : public PlayerState{
public:
	void enter(Hero& hero);
	void exit(Hero& hero);
	void handleInput(Hero& hero, const InputData& data);
	void update(Hero& hero);
private:
	Direction wallDirection_;
};

#endif