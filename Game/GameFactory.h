#ifndef GAME_FACTORY_H
#define GAME_FACTORY_H

#include "Window.h"
#include "Renderer.h"
#include "TextureLoader.h"
#include "TextureCache.h"
#include "GameStateMachine.h"
#include "Input.h"
#include "EntityFactory.h"
#include "AudioPlayer.h"
#include "AnimationCache.h"

// Creates the Game object and all the objects that reside within
class GameFactory {
public:
	Game* createGame();
private:
	// Variables used in lieu of reading from ini file
	const int windowWidth_ = 800;
	const int windowHeight_ = 600;
	const std::string windowName_ = "Basic Platformer";

	SDL_Window* createSDLWindow();
	SDL_Renderer* createSDLRenderer(SDL_Window* sdlWindow);
	Window* createWindow(SDL_Window* window);
	Renderer* createRenderer(SDL_Renderer* sdlRenderer);
	TextureLoader* createTextureLoader(SDL_Renderer* sdlRenderer);
	TextureCache* createTextureCache(TextureLoader* loader);
	AnimationCache* createAnimationCache();
	AudioPlayer* createAudioPlayer();
	EntityFactory* createEntityFactory(TextureCache* textures, AudioPlayer* audio, AnimationCache* animations);
	GameStateMachine* createGameStateMachine(EntityFactory* factory, AudioPlayer* audio);
	Input* createInput();
};

#endif