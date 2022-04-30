#ifndef RENDERER_H
#define RENDERER_H


#include <SDL.h>
#include <memory>
#include "Helpers.h"

class Renderer {
public:
	Renderer(SDL_Renderer* renderer);
	void render(RenderData data);
	void clearScreen();
	void presentScreen();

private:
	std::unique_ptr<SDL_Renderer, SDL_Deleter> renderer_;
};

#endif