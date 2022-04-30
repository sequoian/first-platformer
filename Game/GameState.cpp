#include "GameState.h"
#include "Game.h"



void GameState::setMachine(GameStateMachine* machine) {
	machine_ = machine;
}

void GameState::changeState(GameState* state) {
	machine_->changeState(state);
}

void GameState::pushState(GameState* state) {
	machine_->pushState(state);
}

void GameState::popState() {
	machine_->popState();
}

