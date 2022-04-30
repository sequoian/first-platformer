#ifndef GAME_H
#define GAME_H

#include <stack>
#include "Helpers.h"
#include "GameState.h"
#include <SDL.h>
#include <memory>
#include "Window.h"
#include "Renderer.h"
#include "Input.h"
#include "TextureCache.h"


class TextureLoader;

class Game {
public:
	Game(Window* window, Renderer* renderer, Input* input, GameStateMachine* machine, TextureCache* textureCache, AnimationCache* animationCache);
	~Game();

	// Housekeeping
	//void init();
	//void cleanup();

	// Game loop
	void mainLoop();
	void lazyLoop();

	void pollForEvents();
	void handleInput();
	void update();
	void render();

	// getters
	bool isRunning();

	// setters
	void quit();

private:
	bool running_;
	std::unique_ptr<Window> window_;
	std::unique_ptr<Renderer> renderer_;
	std::unique_ptr<Input> input_;
	std::unique_ptr<GameStateMachine> stateMachine_;
	std::unique_ptr<TextureCache> textureCache_;
	std::unique_ptr<AnimationCache> animationCache_;
	

};

#endif