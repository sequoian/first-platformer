#ifndef MAIN_BUTTON_H_INCLUDED
#define MAIN_BUTTON_H_INCLUDED

#include <memory>
#include "MainMenu.h"
#include "Helpers.h"

class MainMenu;

/*
TODO : Templatize all buttons
*/

class MainButton {
public:
	MainButton(int x, int y, MainMenu* menu, SDL_Texture* activeTexture, SDL_Texture* inactiveTexture);
	virtual void handleInput(InputData data) {};
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
	MainMenu* menu_;
	std::unique_ptr<SDL_Texture, SDL_Deleter> activeTexture_;
	std::unique_ptr<SDL_Texture, SDL_Deleter> inactiveTexture_;
	

};

#endif