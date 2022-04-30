#include <iostream>
#include "Helpers.h"
#include "Game.h"
#include "Options.h"
#include "Stage.h"
#include "SaveGame.h"

//#include "MainPlayButton.h"


Options::Options(EntityFactory* entityFactory, AudioPlayer* audio) {

	header_ = new OptionButton(290, 150, this,
		entityFactory->getText("Options", 50, { 150, 55, 55 }),
		entityFactory->getText("Options", 50, { 255, 255, 255 }));


	OptionButton* button = new OptionButton(300, 350, this,
		entityFactory->getText("Sound Volume", 20, { 150, 55, 55 }),
		entityFactory->getText("Sound Volume", 20, { 255, 255, 255 }));

	buttons_.push_back(button);

	button = new OptionButton(300, 400, this,
		entityFactory->getText("Music Volume", 20, { 150, 55, 55 }),
		entityFactory->getText("Music Volume", 20, { 255, 255, 255 }));

	buttons_.push_back(button);





	activeButtonIndex_ = 0;
	activeButton_ = buttons_[0];
	activeButton_->enter();

	audio_ = audio;

	makeSoundVolumes(entityFactory);
	makeMusicVolumes(entityFactory);

	soundVolume_ = audio_->getSoundVolume();
	musicVolume_ = audio_->getMusicVolume();
	activeSoundButton_ = soundVolumes_[soundVolume_];
	activeMusicButton_ = musicVolumes_[musicVolume_];

	//text_ = entityFactory->getText("<  Level 21 - Bold  >", 20, { 150, 55, 55 });
}

Options::~Options() {
	for (int i = 0; i < buttons_.size(); ++i) {
		delete buttons_[i];
	}

	for (int i = 0; i < soundVolumes_.size(); ++i) {
		delete soundVolumes_[i];
	}

	for (int i = 0; i < musicVolumes_.size(); ++i) {
		delete musicVolumes_[i];
	}
	



	delete header_;
}

void Options::makeSoundVolumes(EntityFactory* entityFactory) {

	OptionButton* button;

	for (int i = 0; i < 11; ++i) {
		button = new OptionButton(500, 350, this,
			entityFactory->getText(std::to_string(i), 20, { 150, 55, 55 }),
			entityFactory->getText(std::to_string(i), 20, { 255, 255, 255 }));
		soundVolumes_.push_back(button);
	}




}

void Options::makeMusicVolumes(EntityFactory* entityFactory) {
	OptionButton* button;

	for (int i = 0; i < 11; ++i) {
		button = new OptionButton(500, 400, this,
			entityFactory->getText(std::to_string(i), 20, { 150, 55, 55 }),
			entityFactory->getText(std::to_string(i), 20, { 255, 255, 255 }));
		musicVolumes_.push_back(button);
	}
}

void Options::enter() {
	//std::cout << "Entered Menu" << std::endl;
}

void Options::exit() {
	SaveGame::getInstance().setSoundVolume(soundVolume_);
	SaveGame::getInstance().setMusicVolume(musicVolume_);
}

void Options::handleInput(Game* game, InputData* input) {
	if (input->quit) {
		game->quit();
	}
	if (input->upHeld && !input->upHeldPreviously) {
		previousButton();
	}
	else if (input->downHeld && !input->downHeldPreviously) {
		nextButton();
	}
	if (input->rightHeld && !input->rightHeldPreviously) {
		raiseVolume();
	}
	else if (input->leftHeld && !input->leftHeldPreviously) {
		lowerVolume();
	}
	if (input->runHeld) {
		audio_->playSoundEffect(SoundEffect::Back);
		machine_->popState();
	}
	else if (input->pauseHeld && !input->pauseHeldPreviously) {
		audio_->playSoundEffect(SoundEffect::Back);
		popState();
	}

	//activeButton_->handleInput(input);
}

void Options::update(Game* game) {
	// update
}

void Options::render(Game* game, Renderer* renderer) {

	//renderer->clearScreen();

	renderer->render(header_->getRenderData());

	for (int i = 0; i < buttons_.size(); ++i) {
		renderer->render(buttons_[i]->getRenderData());
	}

	renderer->render(activeSoundButton_->getRenderData());
	renderer->render(activeMusicButton_->getRenderData());

	//renderer->presentScreen();

}

void Options::nextButton() {
	if (activeButtonIndex_ == buttons_.size() - 1) {
		activeButtonIndex_ = 0;
	}
	else {
		++activeButtonIndex_;
	}
	audio_->playSoundEffect(SoundEffect::Navigate);
	changeButton();
}

void Options::previousButton() {
	if (activeButtonIndex_ == 0) {
		activeButtonIndex_ = buttons_.size() - 1;
	}
	else {
		--activeButtonIndex_;
	}
	audio_->playSoundEffect(SoundEffect::Navigate);

	changeButton();
}

void Options::changeButton() {
	activeButton_->exit();
	activeButton_ = buttons_[activeButtonIndex_];
	activeButton_->enter();

}


void Options::lowerVolume() {
	switch (activeButtonIndex_) {
	case 0: {
		if (soundVolume_ != 0) {
			--soundVolume_;
			activeSoundButton_ = soundVolumes_[soundVolume_];
			audio_->setSoundVolume(soundVolume_);
			audio_->playSoundEffect(SoundEffect::Jump);
		}
		break;
	}
	case 1: {
		if (musicVolume_ != 0) {
			--musicVolume_;
			activeMusicButton_ = musicVolumes_[musicVolume_];
			audio_->setMusicVolume(musicVolume_);
		}
		break;
	}
	}
}

void Options::raiseVolume() {
	switch (activeButtonIndex_) {
	case 0: {
		if (soundVolume_ != 10) {
			++soundVolume_;
			activeSoundButton_ = soundVolumes_[soundVolume_];
			audio_->setSoundVolume(soundVolume_);
			audio_->playSoundEffect(SoundEffect::Jump);
		}
		break;
	}
	case 1: {
		if (musicVolume_ != 10) {
			++musicVolume_;
			activeMusicButton_ = musicVolumes_[musicVolume_];
			audio_->setMusicVolume(musicVolume_);
		}
		break;
	}
	}
}