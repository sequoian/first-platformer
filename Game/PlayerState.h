#ifndef PLAYER_STATE_H_INCLUDED
#define PLAYER_STATE_H_INCLUDED

struct InputData;
class Hero;
class PlayerStateMachine;

class PlayerState {
public:
	virtual ~PlayerState() {};
	virtual void enter(Hero& hero) = 0;
	virtual void exit(Hero& hero) = 0;
	virtual void handleInput(Hero& hero, const InputData& data) = 0;
	virtual void update(Hero& hero) = 0;
};

#endif