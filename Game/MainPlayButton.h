#ifndef MAIN_PLAY_BUTTON_H_INCLUDED
#define MAIN_PLAY_BUTTON_H_INCLUDED

#include "MainButton.h" 

class MainPlayButton : public MainButton {
public:
	MainPlayButton(int x, int y, MainMenu* menu, SDL_Texture* activeTexture, SDL_Texture* inactiveTexture);
	void handleInput(InputData data);
};

#endif