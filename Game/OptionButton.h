#ifndef MAIN_BUTTON_H_INCLUDED
#define MAIN_BUTTON_H_INCLUDED

#include <memory>
#include "Options.h"
#include "Helpers.h"

class Options;

class OptionButton {
public:
	OptionButton(int x, int y, Options* menu, SDL_Texture* activeTexture, SDL_Texture* inactiveTexture);
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
	Options* menu_;
	std::unique_ptr<SDL_Texture, SDL_Deleter> activeTexture_;
	std::unique_ptr<SDL_Texture, SDL_Deleter> inactiveTexture_;
	//int volume_;

	//void raiseVolume(AudioPlayer* audio);
	//void lowerVolume(AudioPlayer* audio);


};

#endif