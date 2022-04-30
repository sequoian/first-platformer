#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>
#include <memory>
#include "Helpers.h"

class Window {
public:
	Window(SDL_Window* window, int width, int height);

private:
	std::unique_ptr<SDL_Window, SDL_Deleter> window_;
	int width_;
	int height_;
};

#endif