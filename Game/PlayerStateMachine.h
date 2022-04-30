#ifndef PLAYER_STATE_MACHINE_INCLUDED
#define PLAYER_STATE_MACHINE_INCLUDED

#include "Helpers.h"

class PlayerState;
class Hero;

class PlayerStateMachine {
public:
	PlayerStateMachine(Hero& hero);
	~PlayerStateMachine();
	void changeState(PlayerState* state);
	void handleInput(Hero& hero, const InputData& data);
	void update(Hero& hero);
	void enterFirstState();
private:
	Hero& owner_;
	PlayerState* currentState_;
	PlayerState* globalState_;
};

#endif