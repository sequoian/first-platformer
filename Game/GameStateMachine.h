#ifndef GAME_STATE_MACHINE_H
#define GAME_STATE_MACHINE_H


#include "GameState.h"
#include <stack>
#include <memory>
#include <vector>
#include <string>
#include "EntityFactory.h"
#include "AudioPlayer.h"

class GameState;
class EntityFactory;


class GameStateMachine {
public:
	GameStateMachine(EntityFactory* entityFactory, AudioPlayer* audio);
	~GameStateMachine();
	void changeState(GameState* state);
	void pushState(GameState* state);
	void popState();
	GameState* getCurrentState();
	void launchStage(int stageNumber);
	std::vector<std::string> getStages() const;
	void enterOpeningState();

	void startStages();
	void startMenus();


private:
	std::stack<GameState*> activeStates_;
	std::unique_ptr<EntityFactory> entityFactory_;
	std::unique_ptr<AudioPlayer> audioPlayer_;
	std::vector<std::string> stages_;
	bool inStages_;
	bool inMenus_;


	void addState(GameState* state);
	void removeTopState();
	void removeAllStates();
	void makeStages();
};

#endif