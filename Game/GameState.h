#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "GameStateMachine.h"
#include "Renderer.h"
#include "AudioPlayer.h"

class Game;
class GameStateMachine;
class Entity;
struct InputData;

class GameState {
public:
	GameState() { done_ = false; };
	virtual ~GameState() {};

	virtual void enter() {};
	virtual void exit() {};

	virtual void handleInput(Game* game, InputData* input) {};
	virtual void update(Game* game) {};
	virtual void render(Game* game, Renderer* renderer) {};

	virtual void pause() {};
	virtual void resume() {};

	virtual void addEntity(Entity* entity) {};

	void setMachine(GameStateMachine* machine);
	void changeState(GameState* state);
	void pushState(GameState* state);
	void popState();
	virtual void launchNextStage() {};

	bool done_;

	virtual void victory() {};

protected:
	GameStateMachine* machine_;

};

#endif