#include "TextureLoader.h"
#include <iostream>
#include <SDL_image.h>

TextureLoader::TextureLoader(SDL_Renderer* renderer) {
	renderer_ = renderer;
}

SDL_Texture* TextureLoader::loadTexture(std::string filePath) {
	SDL_Surface* surface = loadPNG(filePath);
	SDL_Texture* texture = convertSurfaceToTexture(surface);
	SDL_FreeSurface(surface);
	return texture;

}

SDL_Surface* TextureLoader::loadPNG(std::string filePath) {
	SDL_Surface* surface = IMG_Load(filePath.c_str());
	if (surface == NULL) {
		std::cout << "Surface loading failed." << std::endl;
	}
	return surface;

}

SDL_Texture* TextureLoader::convertSurfaceToTexture(SDL_Surface* surface) {
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer_, surface);
	if (texture == NULL) {
		std::cout << "Texture creation failed." << std::endl;
	}
	return texture;
}

SDL_Texture* TextureLoader::loadText(std::string content, int fontSize, SDL_Color color) {
	TTF_Font* font = TTF_OpenFont(fontPath_, fontSize);
	if (font == NULL) {
		std::cout << "Font not found." << std::endl;
	}
	SDL_Surface* surface = TTF_RenderText_Solid(font, content.c_str(), color);
	if (surface == NULL) {
		std::cout << "Surface loading failed." << std::endl;
	}
	SDL_Texture* texture = convertSurfaceToTexture(surface);
	SDL_FreeSurface(surface);
	TTF_CloseFont(font);
	return texture;
}