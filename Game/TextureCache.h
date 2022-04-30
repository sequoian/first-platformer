#ifndef TEXTURE_CACHE_H
#define TEXTURE_CACHE_H

#include <SDL.h>
#include <map>
#include "Helpers.h"
#include "TextureLoader.h"
#include <memory>

class TextureCache {
public:
	TextureCache(TextureLoader* loader);
	SDL_Texture* getTexture(TextureName name);
	SDL_Texture* getText(std::string content, int fontSize, SDL_Color color);
private:
	std::map<TextureName, std::unique_ptr<SDL_Texture, SDL_Deleter>> textures_;
	std::unique_ptr<TextureLoader> loader_;
};

#endif