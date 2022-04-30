#include <SDL.h>
#include "Input.h"
#include <iostream>

Input::Input() : inputData_(false) {

}

// Updates input data 
void Input::pollForEvents() {

	storePreviousInput();

	SDL_Event event;
	// iterate through the event queue
	while (SDL_PollEvent(&event)) {
		// window closed
		if (event.type == SDL_QUIT)
			inputData_.quit = true;
		// keyboard key pressed
		if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
			switch (event.key.keysym.sym) {
			case SDLK_LEFT:
				inputData_.leftHeld = true; 
				break;
			case SDLK_RIGHT:
				inputData_.rightHeld = true; 
				break;
			case SDLK_UP:
				inputData_.upHeld = true;
				break;
			case SDLK_DOWN:
				inputData_.downHeld = true;
				break;
			case SDLK_z:
				inputData_.jumpHeld = true;
				break;
			case SDLK_x:
				inputData_.runHeld = true; 
				break;
			case SDLK_ESCAPE:
				inputData_.pauseHeld = true;
				break;
			case SDLK_0:
				inputData_.skipHeld = true;
				break;
			case SDLK_j:
				inputData_.restartHeld = true;
				break;
			}


		}
		// keyboard key released
		else if (event.type == SDL_KEYUP && event.key.repeat == 0) {
			switch (event.key.keysym.sym) {
			case SDLK_LEFT:
				inputData_.leftHeld = false; 
				break;
			case SDLK_RIGHT:
				inputData_.rightHeld = false; 
				break;
			case SDLK_UP:
				inputData_.upHeld = false;
				break;
			case SDLK_DOWN:
				inputData_.downHeld = false;
				break;
			case SDLK_z:
				inputData_.jumpHeld = false;				
				break;
			case SDLK_x:
				inputData_.runHeld = false; 
				break;
			case SDLK_ESCAPE:
				inputData_.pauseHeld = false;
				break;
			case SDLK_0:
				inputData_.skipHeld = false;
				break;
			case SDLK_j:
				inputData_.restartHeld = false;
				break;
			}
		}	
	}
}

InputData Input::getData() {
	return inputData_;
}

// Stores previous input for functions that need that information
void Input::storePreviousInput() {
	inputData_.jumpHeldPreviously = inputData_.jumpHeld;
	inputData_.pauseHeldPreviously = inputData_.pauseHeld;
	inputData_.leftHeldPreviously = inputData_.leftHeld;
	inputData_.rightHeldPreviously = inputData_.rightHeld;
	inputData_.upHeldPreviously = inputData_.upHeld;
	inputData_.downHeldPreviously = inputData_.downHeld;
	inputData_.restartHeldPreviously = inputData_.restartHeld;
	inputData_.skipHeldPreviously = inputData_.skipHeld;
}
