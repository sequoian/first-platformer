#include <SDL.h>
#include "GameStateMachine.h"
#include "SaveGame.h"

// opening state
#include "MainMenu.h"
#include "Stage.h"

GameStateMachine::GameStateMachine(EntityFactory* entityFactory, AudioPlayer* audio) {
	// Add opening state.  Make sure opening state is #included
	audioPlayer_ = std::unique_ptr<AudioPlayer>(audio);
	entityFactory_ = std::unique_ptr<EntityFactory>(entityFactory);
	makeStages();

	bool flag = SaveGame::getInstance().checkStageAmount(stages_.size());
	//std::cout << "Stage Amount Flag: " << flag << std::endl;

	inStages_ = false;
	inMenus_ = false;
	

	//launchStage(0);
	
	//startMenus();
}

GameStateMachine::~GameStateMachine() {
	removeAllStates();
}

void GameStateMachine::changeState(GameState* state) {
	if (!activeStates_.empty()) {
		removeTopState();
	}
	addState(state);
}

void GameStateMachine::pushState(GameState* state) {
	if (!activeStates_.empty()) {
		activeStates_.top()->pause();
	}
	addState(state);
}

void GameStateMachine::popState() {
	if (!activeStates_.empty()) {
		removeTopState();
	}
	if (!activeStates_.empty()) {
		activeStates_.top()->resume();
	}
}

GameState* GameStateMachine::getCurrentState() {
	return activeStates_.top();
}

void GameStateMachine::addState(GameState* state) {
	activeStates_.push(state);
	activeStates_.top()->setMachine(this);
	activeStates_.top()->enter();
}

void GameStateMachine::removeTopState() {
	activeStates_.top()->exit();
	delete activeStates_.top();
	activeStates_.pop();
}

void GameStateMachine::removeAllStates() {
	while (!activeStates_.empty()) {
		removeTopState();
	}
}

void GameStateMachine::launchStage(int stageNumber) {
	// loop the stages from end back to beginning
	if (stageNumber > stages_.size() - 1) {
		stageNumber = 0;
	}
	changeState(
		new Stage(entityFactory_.get(), *audioPlayer_.get(), stages_[stageNumber], stageNumber)
	);
}

std::vector<std::string> GameStateMachine::getStages() const {
	return stages_;
}

void GameStateMachine::startStages() {
	if (!inStages_) {
		inStages_ = true;
		inMenus_ = false;
		audioPlayer_->playMusicTrack(MusicTrack::VVVVVV);
	}
}

void GameStateMachine::startMenus() {
	if (!inMenus_) {
		inMenus_ = true;
		inStages_ = false;
		audioPlayer_->playMusicTrack(MusicTrack::Quickman);
	}
}

void GameStateMachine::enterOpeningState() {
	addState(new MainMenu(entityFactory_.get(), audioPlayer_.get()));
}

void GameStateMachine::makeStages() {
	const std::string path = "Stages/";
	const std::string extension = ".txt";

	// apprentice
	stages_.push_back(path + "Hello" + extension);
	stages_.push_back(path + "World" + extension);
	stages_.push_back(path + "Gap" + extension);
	stages_.push_back(path + "Danger" + extension);
	stages_.push_back(path + "Long" + extension);
	stages_.push_back(path + "Longer" + extension);
	stages_.push_back(path + "Well" + extension);
	stages_.push_back(path + "Illusion" + extension);
	stages_.push_back(path + "Growth" + extension);
	stages_.push_back(path + "Control" + extension);
	stages_.push_back(path + "Physics" + extension);
	stages_.push_back(path + "Needles" + extension);
	stages_.push_back(path + "Platforms" + extension);
	stages_.push_back(path + "Hills" + extension);
	stages_.push_back(path + "Arch" + extension);

	// journeyman
	stages_.push_back(path + "Smile" + extension);
	stages_.push_back(path + "Speckles" + extension);	
	stages_.push_back(path + "Step_Lightly" + extension);
	stages_.push_back(path + "Agile" + extension);
	stages_.push_back(path + "Longest" + extension);
	stages_.push_back(path + "Softly" + extension);
	stages_.push_back(path + "Meander" + extension);
	stages_.push_back(path + "Assist" + extension);
	stages_.push_back(path + "Heave" + extension);
	stages_.push_back(path + "Free" + extension);
	stages_.push_back(path + "Squigle" + extension);
	stages_.push_back(path + "Teeth" + extension);
	stages_.push_back(path + "Character" + extension);

	// skilled
	stages_.push_back(path + "Stars" + extension);
	stages_.push_back(path + "Hypotenuse" + extension);
	stages_.push_back(path + "Speckles_Return" + extension);
	stages_.push_back(path + "Lava" + extension);
	stages_.push_back(path + "Light_Touch" + extension);
	stages_.push_back(path + "Eye" + extension);
	stages_.push_back(path + "Snake" + extension);
	stages_.push_back(path + "Indigestion" + extension);
	stages_.push_back(path + "Down" + extension);
	stages_.push_back(path + "Bang" + extension);
	stages_.push_back(path + "Worm" + extension);

	// master
	stages_.push_back(path + "Pressure" + extension);
	stages_.push_back(path + "Right_Side" + extension);
	stages_.push_back(path + "Wrong_Side" + extension);
	stages_.push_back(path + "Dance" + extension);
	stages_.push_back(path + "Dark_Arch" + extension);
	stages_.push_back(path + "Cave" + extension);
	stages_.push_back(path + "Death" + extension);
	stages_.push_back(path + "No_Rest" + extension);
	stages_.push_back(path + "Tight_Fit" + extension);
	stages_.push_back(path + "Troll" + extension);
	stages_.push_back(path + "Endurance" + extension);
}