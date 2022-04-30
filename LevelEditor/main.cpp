/* Basic Template for an SDL2 program */
#include <SDL.h>
#include <string>
#include "Input.h"
#include "Cursor.h"
#include "Canvas.h"
#include "CanvasLoader.h"
#include "Globals.h"
#include <iostream>
#include "Viewport.h"

//memory leaks
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int main(int argc, char* args[]) {

	//Testing for memory leaks
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	{

	// Create a window
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("Level Editor", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		800, 600, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	const std::string file = "Images/tiles.bmp";
	SDL_Surface* loadedImage = SDL_LoadBMP(file.c_str());
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, loadedImage);
	SDL_FreeSurface(loadedImage);

	Input input;
	//Canvas canvas(800, 600, 20, 20, texture);
	//Cursor cursor(&canvas, texture);
	// Leave window open for a while

	bool running = true;

	CanvasLoader loader;
	SDL_HideWindow(window);
	Canvas* canvas = loader.getCanvas(texture);
	Cursor cursor(canvas, texture);
	SDL_ShowWindow(window);
	SDL_RaiseWindow(window);

	Viewport viewport;

	while (running) {
		input.pollForEvents();
		InputData data = input.getData();
		if (data.quit)
			running = false;
		if (data.saveHeld && !data.saveHeldPreviously) {
			canvas->write(g_fileName);
			std::cout << "Saved..." << std::endl;
		}
		viewport.handleInput(data);
		viewport.update();
		cursor.input(data, viewport);
		SDL_RenderClear(renderer);
		canvas->render(renderer, viewport);
		SDL_RenderPresent(renderer);
	}

	canvas->write("backup");

	// Close program
	delete canvas;
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	// end memory leaks
	}
	_CrtDumpMemoryLeaks();

	return 0;
}