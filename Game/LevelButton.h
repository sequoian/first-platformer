#ifndef LEVEL_BUTTON_H_INCLUDED
#define LEVEL_BUTTON_H_INCLUDED

#include <memory>
#include "LevelSelect.h"
#include "Helpers.h"

class LevelSelect;

class LevelButton {
public:
	LevelButton(int x, int y, LevelSelect* menu, SDL_Texture* activeTexture, SDL_Texture* inactiveTexture);
	void handleInput(InputData data) {};
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
	LevelSelect* menu_;
	std::unique_ptr<SDL_Texture, SDL_Deleter> activeTexture_;
	std::unique_ptr<SDL_Texture, SDL_Deleter> inactiveTexture_;


};

#endif