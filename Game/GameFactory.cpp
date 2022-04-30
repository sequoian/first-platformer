#include <iostream>
#include <string>
#include "Game.h"
#include "GameFactory.h"

Game* GameFactory::createGame() {
	SDL_Window* sdlWindow = createSDLWindow();
	SDL_Renderer* sdlRenderer = createSDLRenderer(sdlWindow);
	Window* window = createWindow(sdlWindow);
	Renderer* renderer = createRenderer(sdlRenderer);
	TextureLoader* textureLoader = createTextureLoader(sdlRenderer);
	TextureCache* textureCache = createTextureCache(textureLoader);
	AnimationCache* animationCache = createAnimationCache();
	AudioPlayer* audioPlayer = createAudioPlayer();
	EntityFactory* entityFactory = createEntityFactory(textureCache, audioPlayer, animationCache);
	GameStateMachine* machine = createGameStateMachine(entityFactory, audioPlayer);
	Input* input = createInput();

	return new Game(window, renderer, input, machine, textureCache, animationCache);
}

SDL_Window* GameFactory::createSDLWindow() {
	// Read ini or save file here

	// Create the SDL Window (using private values)
	SDL_Window* window = SDL_CreateWindow(windowName_.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
		windowWidth_, windowHeight_, NULL);

	// Check if sdl window was successfully created
	if (window == NULL) {
		std::cout << "Window creation failed." << std::endl;
	}

	return window;
}

SDL_Renderer* GameFactory::createSDLRenderer(SDL_Window* sdlWindow) {
	// Read ini or save file here

	// Create the SDL Renderer
	SDL_Renderer* renderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	// Check if sdl renderer was successfully created
	if (renderer == NULL) {
		std::cout << "Renderer creation failed." << std::endl;
	}

	return renderer;
}

Window* GameFactory::createWindow(SDL_Window* sdlWindow) {
	return new Window(sdlWindow, windowWidth_, windowHeight_);
}

Renderer* GameFactory::createRenderer(SDL_Renderer* sdlRenderer) {
	// Pass interpolator to this function when interpolator is finished

	return new Renderer(sdlRenderer);
}

TextureLoader* GameFactory::createTextureLoader(SDL_Renderer* sdlRenderer) {
	return new TextureLoader(sdlRenderer);
}

TextureCache*  GameFactory::createTextureCache(TextureLoader* loader) {
	return new TextureCache(loader);
}

AnimationCache* GameFactory::createAnimationCache() {
	return new AnimationCache;
}

AudioPlayer* GameFactory::createAudioPlayer() {
	return new AudioPlayer;
}

EntityFactory* GameFactory::createEntityFactory(TextureCache* textures, AudioPlayer* audio, AnimationCache* animations) {
	return new EntityFactory(textures, audio, animations);
}

GameStateMachine* GameFactory::createGameStateMachine(EntityFactory* factory, AudioPlayer* audio) {
	return new GameStateMachine(factory, audio);
}

Input* GameFactory::createInput() {
	return new Input;
}


