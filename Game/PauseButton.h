#pragma once

#include <memory>
#include "PauseScreen.h"
#include "Helpers.h"

class PauseScreen;

class PauseButton {
public:
	PauseButton(int x, int y, PauseScreen* menu, SDL_Texture* activeTexture, SDL_Texture* inactiveTexture);
	void handleInput(InputData data, AudioPlayer* audio) {};
	virtual void enter() {
		active_ = true;
	};
	virtual void exit() {
		active_ = false;
	};
	virtual RenderData getRenderData();

protected:
	SDL_Rect renderBox_;
	bool active_;
	PauseScreen* menu_;
	std::unique_ptr<SDL_Texture, SDL_Deleter> activeTexture_;
	std::unique_ptr<SDL_Texture, SDL_Deleter> inactiveTexture_;
	//int volume_;

	//void raiseVolume(AudioPlayer* audio);
	//void lowerVolume(AudioPlayer* audio);


};