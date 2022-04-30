#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Game.h"
#include "Input.h"
#include "FramesPerSecond.h"
#include "TimeStep.h"
#include "Interpolator.h"

Game::Game(Window* window, Renderer* renderer, Input* input, GameStateMachine* machine, TextureCache* textureCache, AnimationCache* animationCache) {
	window_ = std::unique_ptr<Window>(window);
	renderer_ = std::unique_ptr<Renderer>(renderer);
	input_ = std::unique_ptr<Input>(input);
	stateMachine_ = std::unique_ptr<GameStateMachine>(machine);
	textureCache_ = std::unique_ptr<TextureCache>(textureCache);
	animationCache_ = std::unique_ptr<AnimationCache>(animationCache);

	running_ = true;

	machine->enterOpeningState();

}

Game::~Game() {
	//std::cout << "Game destroyed..." << std::endl;
}

void Game::mainLoop() {
	TimeStep timeStep(5, g_TimeStepFPS);
	FramesPerSecond fps(50);
	while (isRunning()) {
		while (timeStep.canUpdate()) {
			pollForEvents();
			handleInput();
			update();
			//std::cout << "update" << std::endl;
		}
		Interpolator::getInstance().setRemainder(timeStep.getRemainder());
		render();
		fps.tick();
		//std::cout << fps.getCount() << std::endl;
		//std::cout << "render" << std::endl;
	}
}

void Game::lazyLoop() {
	FramesPerSecond fps(50);
	while (isRunning()) {
		pollForEvents();
		handleInput();
		update();
		render();
		fps.tick();
		//std::cout << fps.getCount() << std::endl;
	}
}

void Game::pollForEvents() {
	input_->pollForEvents();
}

void Game::handleInput() {
	InputData data = input_->getData();
	stateMachine_->getCurrentState()->handleInput(this, &data);
}

void Game::update() {
	stateMachine_->getCurrentState()->update(this);
}

void Game::render() {
	renderer_.get()->clearScreen();
	stateMachine_->getCurrentState()->render(this, renderer_.get());
	renderer_.get()->presentScreen();
}

bool Game::isRunning() {
	return running_;
}

void Game::quit() {
	running_ = false;
}
