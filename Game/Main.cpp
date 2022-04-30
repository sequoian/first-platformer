/* Basic Template for an SDL2 program */
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <memory>
#include "Game.h"

#include "Input.h"
#include "Window.h"
#include "Renderer.h"
#include "TextureCache.h"
#include "TextureLoader.h"
#include "GameFactory.h"
#include "FramesPerSecond.h"
#include "SaveGame.h"


 //memory leaks
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

void startSDL();
void endSDL();

int main(int argc, char* args[]) {

	//Testing for memory leaks
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	{

	startSDL();
	
	SaveGame::getInstance().readFile();

	GameFactory factory;
	std::unique_ptr<Game> game (factory.createGame());



	game->lazyLoop();
	

	SaveGame::getInstance().writeFile();

	// end memory leaks
	}
	_CrtDumpMemoryLeaks();

	// Ending SDL Before the rest of the objects go out of scope causes chaos!
	endSDL();

	return 0;

}

void startSDL() {
	// Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "SDL failed to initialize." << std::endl;
	}
	// Initialize SDL Image
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) {
		std::cout << "SDL Image failed to initialize." << std::endl;
	}
	//Initialize SDL Mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		assert(false);
	}
	// Initialize SDL True Type Font
	if (TTF_Init() == -1) {
		assert(false);
	}
}

void endSDL() {
	TTF_Quit();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}