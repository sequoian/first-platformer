#include "Window.h"

Window::Window(SDL_Window* window, int width, int height) {
	window_ = std::unique_ptr<SDL_Window, SDL_Deleter> (window, SDL_Deleter());
	width_ = width;
	height_ = height;
}