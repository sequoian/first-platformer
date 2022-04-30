#include "Renderer.h"

Renderer::Renderer(SDL_Renderer* renderer) {
	renderer_ = std::unique_ptr<SDL_Renderer, SDL_Deleter> (renderer, SDL_Deleter());
	/*
	TODO
	Can scale the rendered image, but linear filtering causes bleeding in textures.
	Possible solutions: half-pixel offset and opengl clamp
	*/
	//SDL_RenderSetScale(renderer_.get(), 1.5, 1.5);
	//SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	//SDL_RenderSetLogicalSize(renderer_.get(), 400, 300);

	//SDL_SetRenderDrawColor(renderer_.get(), 127, 127, 127, 255);
}

// Adds an entity's rendering data to the renderer
void Renderer::render(RenderData data) {
	/* Modify destination using Interpolator here*/

	// Add the render data to the renderer
	SDL_RenderCopyEx(renderer_.get(), data.texture, data.source, data.destination, 0, NULL, data.flip);
}

// Clears the screen of images
void Renderer::clearScreen() {
	SDL_RenderClear(renderer_.get());
}

// Presents the data in the renderer onto the screen
void Renderer::presentScreen() {
	SDL_RenderPresent(renderer_.get());
}
