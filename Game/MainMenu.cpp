#include <iostream>
#include "Helpers.h"
#include "Game.h"
#include "MainMenu.h"
#include "Stage.h"
#include "Options.h"
#include "LevelSelect.h"
//#include "MainPlayButton.h"


MainMenu::MainMenu(EntityFactory* entityFactory, AudioPlayer* audio) {

	header_ = new MainButton(50, 150, this,
		entityFactory->getText("Super Red Cube Guy 64", 50, { 150, 55, 55 }),
		entityFactory->getText("Super Red Cube Guy 64", 50, { 255, 255, 255 }));


	MainButton* button = new MainButton(300, 350, this,
		entityFactory->getText("Play", 20, { 150, 55, 55 }),
		entityFactory->getText("Play", 20, { 255, 255, 255 }));

	buttons_.push_back(button);

	button = new MainButton(300, 400, this,
		entityFactory->getText("Options", 20, { 150, 55, 55 }),
		entityFactory->getText("Options", 20, { 255, 255, 255 }));

	buttons_.push_back(button);

	button = new MainButton(300, 450, this,
		entityFactory->getText("Exit", 20, { 150, 55, 55 }),
		entityFactory->getText("Exit", 20, { 255, 255, 255 }));

	buttons_.push_back(button);

	activeButtonIndex_ = 0;
	activeButton_ = buttons_[0];
	activeButton_->enter();

	factory_ = entityFactory;

	audio_ = audio;

	

	//audio_->playMusicTrack(MusicTrack::Quickman);

	//text_ = entityFactory->getText("<  Level 21 - Bold  >", 20, { 150, 55, 55 });
}

MainMenu::~MainMenu() {
	for (int i = 0; i < buttons_.size(); ++i) {
		delete buttons_[i];
	}

	delete header_;
}

void MainMenu::enter() {
	//std::cout << "Entered Menu" << std::endl;
	machine_->startMenus();
}

void MainMenu::exit() {
	//std::cout << "Exited Menu" << std::endl;
}

void MainMenu::handleInput(Game* game, InputData* input) {
	if (input->quit) {
		game->quit();
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

	//activeButton_->handleInput(input);
}

void MainMenu::update(Game* game) {
	// update
}

void MainMenu::render(Game* game, Renderer* renderer) {
	
	//renderer->clearScreen();

	renderer->render(header_->getRenderData());

	for (int i = 0; i < buttons_.size(); ++i) {
		renderer->render(buttons_[i]->getRenderData());
	}
	//renderer->presentScreen();

}

void MainMenu::nextButton() {
	if (activeButtonIndex_ == buttons_.size() - 1) {
		activeButtonIndex_ = 0;
	}
	else {
		++activeButtonIndex_;
	}
	audio_->playSoundEffect(SoundEffect::Navigate);
	changeButton();
}

void MainMenu::previousButton() {
	if (activeButtonIndex_ == 0 ) {
		activeButtonIndex_ = buttons_.size() - 1;
	}
	else {
		--activeButtonIndex_;
	}
	audio_->playSoundEffect(SoundEffect::Navigate);
	
	changeButton();
}

void MainMenu::changeButton() {
	activeButton_->exit();
	activeButton_ = buttons_[activeButtonIndex_];
	activeButton_->enter();
}

void MainMenu::executeButton(Game* game) {
	switch (activeButtonIndex_) {
	case 0:
		//machine_->launchStage(0);
		audio_->playSoundEffect(SoundEffect::Forward);
		machine_->pushState(new LevelSelect(factory_, audio_));
		break;
	case 1:
		audio_->playSoundEffect(SoundEffect::Forward);
		machine_->pushState(new Options(factory_, audio_));
		break;
	case 2:
		game->quit();
		break;
	}
}