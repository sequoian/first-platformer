#include <iostream>
#include "Helpers.h"
#include "Game.h"
#include "PauseScreen.h"
#include "MainMenu.h"

PauseScreen::PauseScreen(EntityFactory* entityFactory, AudioPlayer* audio, GameState* pausedState) {
	pausedState_ = pausedState;
	audio_ = audio;
	factory_ = entityFactory;

	/*
	header_ = new PauseButton(290, 150, this,
		entityFactory->getText("PAUSED", 50, { 243, 132, 4 }),
		entityFactory->getText("PAUSED", 50, { 0, 0, 0 }));


	PauseButton* button = new PauseButton(300, 250, this,
		entityFactory->getText("Resume", 20, { 243, 132, 4 }),
		entityFactory->getText("Resume", 20, { 0, 0, 0 }));

	buttons_.push_back(button);

	button = new PauseButton(300, 300, this,
		entityFactory->getText("Exit Level", 20, { 243, 132, 4 }),
		entityFactory->getText("Exit Level", 20, { 0, 0, 0 }));

	buttons_.push_back(button);

	button = new PauseButton(300, 350, this,
		entityFactory->getText("Exit Game", 20, { 243, 132, 4 }),
		entityFactory->getText("Exit Game", 20, { 0, 0, 0 }));

	buttons_.push_back(button);
	*/

	header_ = new PauseButton(290, 150, this,
		entityFactory->getText("PAUSED", 50, { 243, 132, 4 }),
		entityFactory->getText("PAUSED", 50, { 0, 0, 0 }));


	PauseButton* button = new PauseButton(320, 220, this,
		entityFactory->getText("Resume", 25, { 243, 132, 4 }),
		entityFactory->getText("Resume", 25, { 0, 0, 0 }));

	buttons_.push_back(button);

	button = new PauseButton(320, 250, this,
		entityFactory->getText("Exit Level", 25, { 243, 132, 4 }),
		entityFactory->getText("Exit Level", 25, { 0, 0, 0 }));

	buttons_.push_back(button);

	button = new PauseButton(320, 280, this,
		entityFactory->getText("Exit Game", 25, { 243, 132, 4 }),
		entityFactory->getText("Exit Game", 25, { 0, 0, 0 }));

	buttons_.push_back(button);

	activeButtonIndex_ = 0;
	activeButton_ = buttons_[activeButtonIndex_];
	activeButton_->enter();
}

PauseScreen::~PauseScreen() {
	for (int i = 0; i < buttons_.size(); ++i) {
		delete buttons_[i];
	}

	delete header_;
}

void PauseScreen::enter() {
	//std::cout << "Entered Pause" << std::endl;
}

void PauseScreen::exit() {
	//std::cout << "Exited Pause" << std::endl;
}

void PauseScreen::handleInput(Game* game, InputData* input) {
	if (input->quit) {
		game->quit();
	}
	if (input->pauseHeld && !input->pauseHeldPreviously) {
		popState();
	}
	if (input->upHeld && !input->upHeldPreviously) {
		previousButton();
	}
	else if (input->downHeld && !input->downHeldPreviously) {
		nextButton();
	}
	if (input->jumpHeld && !input->jumpHeldPreviously) {
		executeButton(game);
	}
}

void PauseScreen::update(Game* game) {
	// update
}

void PauseScreen::render(Game* game, Renderer* renderer) {
	//renderer->clearScreen();

	pausedState_->render(game, renderer);

	renderer->render(header_->getRenderData());

	for (int i = 0; i < buttons_.size(); ++i) {
		renderer->render(buttons_[i]->getRenderData());
	}

	//renderer->presentScreen();
}


void PauseScreen::nextButton() {
	if (activeButtonIndex_ == buttons_.size() - 1) {
		activeButtonIndex_ = 0;
	}
	else {
		++activeButtonIndex_;
	}
	audio_->playSoundEffect(SoundEffect::Navigate);
	changeButton();
}

void PauseScreen::previousButton() {
	if (activeButtonIndex_ == 0) {
		activeButtonIndex_ = buttons_.size() - 1;
	}
	else {
		--activeButtonIndex_;
	}
	audio_->playSoundEffect(SoundEffect::Navigate);

	changeButton();
}

void PauseScreen::changeButton() {
	activeButton_->exit();
	activeButton_ = buttons_[activeButtonIndex_];
	activeButton_->enter();
}

void PauseScreen::executeButton(Game* game) {
	switch (activeButtonIndex_) {
	case 0:
		popState();
		break;
	case 1:
		machine_->changeState(new MainMenu(factory_, audio_));
		break;
	case 2:
		game->quit();
		break;
	}
}