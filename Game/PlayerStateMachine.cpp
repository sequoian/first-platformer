#include "PlayerStateMachine.h"
#include "PlayerState.h"

#include "Global.h"
#include "Standing.h"
#include "Spawning.h"


PlayerStateMachine::PlayerStateMachine(Hero& hero) :
 owner_(hero) {
	globalState_ = new Global;
	globalState_->enter(owner_);

}


PlayerStateMachine::~PlayerStateMachine() {
	globalState_->exit(owner_);
	delete globalState_;
	currentState_->exit(owner_);
	delete currentState_;
}

void PlayerStateMachine::enterFirstState() {
	currentState_ = new Standing;
	currentState_->enter(owner_);
}

void PlayerStateMachine::changeState(PlayerState* state) {
	currentState_->exit(owner_);
	delete currentState_;
	currentState_ = state;
	currentState_->enter(owner_);
}

void PlayerStateMachine::handleInput(Hero& player, const InputData& data) {
	globalState_->handleInput(player, data);
	currentState_->handleInput(player, data);
}

void PlayerStateMachine::update(Hero& player) {
	currentState_->update(player);
	globalState_->update(player);
}