#ifndef ENTITY_FACTORY_H
#define ENTITY_FACTORY_H

#include "TextureCache.h"
#include "GameState.h"
#include "Hero.h"
#include "Helpers.h"
#include "AudioPlayer.h"
#include "AnimationCache.h"

class GameState;

class EntityFactory {
public:
	EntityFactory(TextureCache* textures, AudioPlayer* audio, AnimationCache* animations);
	void createEntities(GameState* gameState);
	void addTimer(Timer* timer);
	void EntityFactory::createEntity(int x, int y, int type, GameState* gameState);

	// for testing
	SDL_Texture* getText(std::string content, int fontSize, SDL_Color color);

private:
	int globalID_;
	TextureCache* textures_;
	AudioPlayer* audio_;
	GameState* gameState_;
	AnimationCache* animations_;
	Timer* timer_;

	void readFile(char* fileName);
	void createEntity(int x, int y, int type);
	int getNewID();

	// possible usage
	void createHero();
	void createSolidTile();
	void createAirTile();

};

#endif