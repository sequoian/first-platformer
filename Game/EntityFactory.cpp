#include "EntityFactory.h"
#include <string>
#include <fstream>
#include <stdlib.h>
#include "SolidTile.h"
#include "AirTile.h"
#include "DamageTile.h"
#include "Effect.h"
#include "StageGoal.h"

EntityFactory::EntityFactory(TextureCache* textures, AudioPlayer* audio, AnimationCache* animations) {
	textures_ = textures;
	audio_ = audio;
	animations_ = animations;
	globalID_ = 0;
}

void EntityFactory::addTimer(Timer* timer) {
	timer_ = timer;
}


void EntityFactory::createEntities(GameState* gameState) {
	char* stageFile = "Stages/Damage.txt";
	gameState_ = gameState;
	readFile(stageFile);
}


void EntityFactory::readFile(char* fileName) {
	std::ifstream file;
	file.open(fileName);
	while (!file.eof()) {
		char line[50];
		file.getline(line, 10, ',');
		int x = atoi(line);
		//std::cout << line << std::endl;
		file.getline(line, 10, ',');
		int y = atoi(line);
		//std::cout << line << std::endl;
		file.getline(line, 30, '\n');
		int type = atoi(line);
		//std::cout << line << std::endl;
		//std::cout << x << ", " << y << ", " << type << std::endl;
		createEntity(x, y, type);
	}
	file.close();

}

void EntityFactory::createEntity(int x, int y, int type, GameState* gameState) {
	Position position = { x, y };
	Entity* newEntity = nullptr;
	SDL_Texture* texture = nullptr;
	SDL_Rect* clip = nullptr;

	switch (type) {
	// Player
	case 0: {
		texture = textures_->getTexture(Texture_RedCube);
		Animator animator = animations_->getAnimator(AnimationCache::Package::Hero);
		animator.setTimer(*timer_);

		// death effect
		SDL_Texture* deathTexture = textures_->getTexture(Texture_CubeDeath);
		Animator deathAnimator = animations_->getAnimator(AnimationCache::HeroDeath);
		deathAnimator.setTimer(*timer_);
		Effect* deathEffect = new Effect(-1, position, deathTexture, deathAnimator, SDL_FLIP_NONE, Animations::HeroDeath);
		// end death effect

		// spawn effect 
		SDL_Texture* spawnTexture = textures_->getTexture(Texture_HeroSpawn);
		Animator spawnAnimator = animations_->getAnimator(AnimationCache::HeroSpawn);
		spawnAnimator.setTimer(*timer_);
		Effect* spawnEffect = new Effect(-1, position, spawnTexture, spawnAnimator, SDL_FLIP_NONE, Animations::Hero_Spawning);
		// end spawn effect

		// victory effect
		SDL_Texture* victoryTexture = textures_->getTexture(Texture_HeroVictory);
		Animator victoryAnimator = animations_->getAnimator(AnimationCache::HeroVictory);
		victoryAnimator.setTimer(*timer_);
		Effect* victoryEffect = new Effect(-1, position, victoryTexture, victoryAnimator, SDL_FLIP_NONE, Animations::Hero_Victory);
		// end victory effect

		newEntity = new Hero(getNewID(), position, texture, audio_, animator, deathEffect, spawnEffect, victoryEffect, 
			gameState, timer_);
		break;
	}
	// Solid Tile
	case 1:
		texture = textures_->getTexture(Texture_Stage);
		clip = new SDL_Rect;
		clip->x = 20;
		clip->y = 0;
		clip->w = 20;
		clip->h = 20;
		newEntity = new SolidTile(getNewID(), position, texture, clip);
		break;
	// Air Tile
	case 2:
		texture = textures_->getTexture(Texture_Stage);
		clip = new SDL_Rect;
		clip->x = 0;
		clip->y = 20;
		clip->w = 20;
		clip->h = 20;
		newEntity = new AirTile(getNewID(), position, texture, clip);
		break;
	// Damage Tile
	case 3:
		texture = textures_->getTexture(Texture_Stage);
		clip = new SDL_Rect;
		clip->x = 20;
		clip->y = 20;
		clip->w = 20;
		clip->h = 20;
		newEntity = new DamageTile(getNewID(), position, texture, clip);
		break;
	// Stage Goal
	case 4:
		texture = textures_->getTexture(Texture_Stage);
		clip = new SDL_Rect;
		clip->x = 0;
		clip->y = 0;
		clip->w = 20;
		clip->h = 20;
		newEntity = new StageGoal(getNewID(), position, texture, gameState, clip);
	}

	gameState->addEntity(newEntity);
}


void EntityFactory::createEntity(int x, int y, int type) {
	Position position = { x, y };
	Entity* newEntity = nullptr;
	SDL_Texture* texture = nullptr;
	SDL_Rect* clip = nullptr;

	switch (type) {
		// Player
	case 0: {
		texture = textures_->getTexture(Texture_RedCube);
		Animator animator = animations_->getAnimator(AnimationCache::Package::Hero);
		animator.setTimer(*timer_);

		// death effect
		SDL_Texture* deathTexture = textures_->getTexture(Texture_CubeDeath);
		Animator deathAnimator = animations_->getAnimator(AnimationCache::HeroDeath);
		deathAnimator.setTimer(*timer_);
		Effect* deathEffect = new Effect(-1, position, deathTexture, deathAnimator, SDL_FLIP_NONE, Animations::HeroDeath); // TODO fix leak
		// end death effect

		// spawn effect 
		SDL_Texture* spawnTexture = textures_->getTexture(Texture_HeroSpawn);
		Animator spawnAnimator = animations_->getAnimator(AnimationCache::HeroSpawn);
		spawnAnimator.setTimer(*timer_);
		Effect* spawnEffect = new Effect(-1, position, spawnTexture, spawnAnimator, SDL_FLIP_NONE, Animations::Hero_Spawning);
		// end spawn effect

		// victory effect
		SDL_Texture* victoryTexture = textures_->getTexture(Texture_HeroVictory);
		Animator victoryAnimator = animations_->getAnimator(AnimationCache::HeroVictory);
		victoryAnimator.setTimer(*timer_);
		Effect* victoryEffect = new Effect(-1, position, victoryTexture, victoryAnimator, SDL_FLIP_NONE, Animations::Hero_Victory);
		// end victory effect
		
		newEntity = new Hero(getNewID(), position, texture, audio_, animator, deathEffect, spawnEffect, victoryEffect, gameState_, timer_);
		break;
	}
		// Solid Tile
	case 1:
		texture = textures_->getTexture(Texture_Stage);
		clip = new SDL_Rect;
		clip->x = 20;
		clip->y = 0;
		clip->w = 20;
		clip->h = 20;
		newEntity = new SolidTile(getNewID(), position, texture, clip);
		break;
		// Air Tile
	case 2:
		texture = textures_->getTexture(Texture_Stage);
		clip = new SDL_Rect;
		clip->x = 0;
		clip->y = 20;
		clip->w = 20;
		clip->h = 20;
		newEntity = new AirTile(getNewID(), position, texture, clip);
		break;
		// Damage Tile
	case 3:
		texture = textures_->getTexture(Texture_Stage);
		clip = new SDL_Rect;
		clip->x = 20;
		clip->y = 20;
		clip->w = 20;
		clip->h = 20;
		newEntity = new DamageTile(getNewID(), position, texture, clip);
		break;
	}

	gameState_->addEntity(newEntity);
}


int EntityFactory::getNewID() {
	int id = globalID_;
	++globalID_;
	return id;

}

void EntityFactory::createHero() {

}

void EntityFactory::createSolidTile() {

}

void EntityFactory::createAirTile() {

}

SDL_Texture* EntityFactory::getText(std::string content, int fontSize, SDL_Color color) {
	return textures_->getText(content, fontSize, color);
}



