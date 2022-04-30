#include <iostream>
#include "Helpers.h"
#include "Game.h"
#include "LevelSelect.h"
#include "Stage.h"

#include "SaveGame.h"
//#include "MainPlayButton.h"


LevelSelect::LevelSelect(EntityFactory* entityFactory, AudioPlayer* audio) {

	header_ = new LevelButton(200, 150, this,
		entityFactory->getText("Select Stage", 30, { 150, 55, 55 }),
		entityFactory->getText("Select Stage", 30, { 255, 255, 255 }));

	entityFactory_ = entityFactory;

	audio_ = audio;
}

LevelSelect::~LevelSelect() {

	for (int i = 0; i < stageButtons_.size(); ++i) {
		delete stageButtons_[i];
	}

	for (int i = 0; i < progressButtons_.size(); ++i) {
		delete progressButtons_[i];
	}

	delete header_;
}

void LevelSelect::makeStageButtons(EntityFactory* entityFactory) {

	std::vector<std::string> stages = machine_->getStages();

	LevelButton* button;

	for (int i = 0; i < stages.size(); ++i) {
		std::string name = stages[i].substr(7, stages[i].size() - 11);
		//std::cout << "Level " << i + 1 << "- " << name << std::endl;
		std::string text = "Level " + std::to_string(i + 1) + " - " + name;
		button = new LevelButton(200, 350, this,
			entityFactory->getText(text, 20, { 250, 219, 63 }),
			entityFactory->getText(text, 20, { 255, 255, 255 }));
		if (SaveGame::getInstance().getStageBeat(i)) {
			button->enter();
		}
		stageButtons_.push_back(button);
	}

	activeButtonIndex_ = SaveGame::getInstance().getLastPlayed();
	activeButton_ = stageButtons_[activeButtonIndex_];
}

void LevelSelect::makeProgressButtons(EntityFactory* entityFactory) {

	SaveGame& save = SaveGame::getInstance();
	
	int numBeaten = save.getNumStagesBeat();
	std::string text = std::to_string(numBeaten);
	LevelButton* button = new LevelButton(200, 550, this,
		entityFactory->getText(text, 20, { 250, 219, 63 }),
		entityFactory->getText(text, 20, { 255, 255, 255 }));
	
	button->enter();
	progressButtons_.push_back(button);

	int numTotal = save.getNumStages();
	text = " / " + std::to_string(numTotal) + "    Completed";
	button = new LevelButton(240, 550, this,
		entityFactory->getText(text, 20, { 250, 219, 63 }),
		entityFactory->getText(text, 20, { 255, 255, 255 }));

	if (numBeaten == numTotal) {
		button->enter();
	}
	progressButtons_.push_back(button);

}

void LevelSelect::enter() {
	//std::cout << "Entered Menu" << std::endl;
	makeStageButtons(entityFactory_);
	makeProgressButtons(entityFactory_);
}

void LevelSelect::exit() {
	//std::cout << "Exited Menu" << std::endl;
}

void LevelSelect::handleInput(Game* game, InputData* input) {
	if (input->quit) {
		game->quit();
	}
	if (input->rightHeld && !input->rightHeldPreviously) {
		nextButton();
	}
	else if (input->leftHeld && !input->leftHeldPreviously) {
		previousButton();
	}
	else if (input->upHeld && !input->upHeldPreviously) {
		previousButton();
	}
	else if (input->downHeld && !input->downHeldPreviously) {
		nextButton();
	}
	if (input->jumpHeld && !input->jumpHeldPreviously) {
		executeButton();
	}
	if (input->runHeld) {
		audio_->playSoundEffect(SoundEffect::Back);
		machine_->popState();
	}
	else if (input->pauseHeld && !input->pauseHeldPreviously) {
		audio_->playSoundEffect(SoundEffect::Back);
		popState();
	}

}

void LevelSelect::update(Game* game) {
}

void LevelSelect::render(Game* game, Renderer* renderer) {

	//renderer->clearScreen();

	renderer->render(header_->getRenderData());

	renderer->render(activeButton_->getRenderData());

	for (int i = 0; i < progressButtons_.size(); ++i) {
		renderer->render(progressButtons_[i]->getRenderData());
	}

	//renderer->presentScreen();

}


void LevelSelect::nextButton() {
	if (activeButtonIndex_ == stageButtons_.size() - 1) {
		activeButtonIndex_ = 0;
	}
	else {
		++activeButtonIndex_;
	}
	audio_->playSoundEffect(SoundEffect::Navigate);
	changeButton();
}

void LevelSelect::previousButton() {
	if (activeButtonIndex_ == 0) {
		activeButtonIndex_ = stageButtons_.size() - 1;
	}
	else {
		--activeButtonIndex_;
	}
	audio_->playSoundEffect(SoundEffect::Navigate);

	changeButton();
}

void LevelSelect::changeButton() {
	//activeButton_->exit();
	activeButton_ = stageButtons_[activeButtonIndex_];
	//activeButton_->enter();

}

void LevelSelect::executeButton() {

	machine_->launchStage(activeButtonIndex_);
	
}
