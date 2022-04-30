#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <memory>

class TextureLoader {
public:
	TextureLoader(SDL_Renderer* renderer);
	SDL_Texture* loadTexture(std::string filePath);
	SDL_Texture* loadText(std::string content, int size, SDL_Color color);

private:
	SDL_Renderer* renderer_;
	const char* fontPath_ = "Images/Fonts/Silkscreen.ttf";

	SDL_Surface* loadPNG(std::string filePath);
	SDL_Texture* convertSurfaceToTexture(SDL_Surface* surface);

};

#endif