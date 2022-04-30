#ifndef SPAWNING_H_INCLUDED
#define SPAWNING_H_INCLUDED

#include "PlayerState.h"
#include "Helpers.h"


class Spawning : public PlayerState{
public:
	void enter(Hero& hero);
	void exit(Hero& hero);
	void handleInput(Hero& hero, const InputData& data);
	void update(Hero& hero);
private:
	bool done_;
	Time spawnStart_;

};

#endif