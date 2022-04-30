#include "MainButton.h"

MainButton::MainButton(int x, int y, MainMenu* menu, SDL_Texture* activeTexture, SDL_Texture* inactiveTexture) {
	active_ = false;
	menu_ = menu;
	activeTexture_ = std::unique_ptr<SDL_Texture, SDL_Deleter>(activeTexture, SDL_Deleter());
	inactiveTexture_ = std::unique_ptr<SDL_Texture, SDL_Deleter>(inactiveTexture, SDL_Deleter());
	renderBox_.x = x;
	renderBox_.y = y;
	SDL_QueryTexture(activeTexture, NULL, NULL, &renderBox_.w, &renderBox_.h);
};

RenderData MainButton::getRenderData() {
	RenderData data;
	if (active_) {
		data.texture = activeTexture_.get();
	}
	else {
		data.texture = inactiveTexture_.get();
	}
	data.destination = &renderBox_;
	data.source = nullptr;
	data.flip = SDL_FLIP_NONE;

	return data;
}