#include "TextureCache.h"

TextureCache::TextureCache(TextureLoader* loader) {
	// set the current loader
	loader_ = std::unique_ptr<TextureLoader> (loader);

	// create the textures and add them to the cache
	SDL_Texture* loadedTexture = loader_->loadTexture("Images/Hero.png");
	textures_[Texture_Hero] = std::unique_ptr<SDL_Texture, SDL_Deleter>(loadedTexture, SDL_Deleter());
	loadedTexture = loader_->loadTexture("Images/Tiles.png");
	textures_[Texture_Stage] = std::unique_ptr<SDL_Texture, SDL_Deleter>(loadedTexture, SDL_Deleter());
	loadedTexture = loader_->loadTexture("Images/RedCube.png");
	textures_[Texture_RedCube] = std::unique_ptr<SDL_Texture, SDL_Deleter>(loadedTexture, SDL_Deleter());
	loadedTexture = loader_->loadTexture("Images/Death.png");
	textures_[Texture_CubeDeath] = std::unique_ptr<SDL_Texture, SDL_Deleter>(loadedTexture, SDL_Deleter());
	loadedTexture = loader_->loadTexture("Images/Spawn.png");
	textures_[Texture_HeroSpawn] = std::unique_ptr<SDL_Texture, SDL_Deleter>(loadedTexture, SDL_Deleter());
	loadedTexture = loader_->loadTexture("Images/Victory.png");
	textures_[Texture_HeroVictory] = std::unique_ptr<SDL_Texture, SDL_Deleter>(loadedTexture, SDL_Deleter());
}

SDL_Texture* TextureCache::getTexture(TextureName name) {
	return textures_[name].get();
}

SDL_Texture* TextureCache::getText(std::string content, int fontSize, SDL_Color color) {
	return loader_.get()->loadText(content, fontSize, color);
}