#include <SDL.h>
#include "Input.h"
#include <iostream>

Input::Input() {
	//inputData.player = false;
	//inputData.solid = false;
	//inputData.damage = false;
	//inputData.air = false;
	inputData.brush = Entity::Entity_AirTile;
	inputData.quit = false;
	inputData.mouseHeld = false;
	inputData.mouseX = 200;
	inputData.mouseY = 200;
	inputData.saveHeld = false;
	inputData.saveHeldPreviously = false;
	inputData.leftHeld = false;
	inputData.rightHeld = false;
	inputData.upHeld = false;
	inputData.downHeld = false;
}

void Input::pollForEvents() {

	// reset non-holding keys
	reset();

	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT)
			inputData.quit = true;
		if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
			switch (event.key.keysym.sym) {
			case SDLK_F1:
				inputData.brush = Entity::Entity_SolidTile; 
				break;
			case SDLK_F2:
				inputData.brush = Entity::Entity_AirTile; 
				break;
			case SDLK_F3:
				inputData.brush = Entity::Entity_Player;
				break;
			case SDLK_F4:
				inputData.brush = Entity::Entity_DamageTile; 
				break;
			case SDLK_F5:
				inputData.brush = Entity::Entity_StageGoal;
				break;
			case SDLK_w:
				inputData.upHeld = true;
				break;
			case SDLK_a:
				inputData.leftHeld = true;
				break;
			case SDLK_s: {
				if (SDL_GetModState() & KMOD_CTRL) {
					inputData.saveHeld = true;
				}
				else {
					inputData.downHeld = true;
				}
				break;
			}
			case SDLK_d:
				inputData.rightHeld = true;
				break;
			}
		}
		
		else if (event.type == SDL_KEYUP && event.key.repeat == 0) {
			switch (event.key.keysym.sym) {
			case SDLK_w:
				inputData.upHeld = false;
				break;
			case SDLK_a:
				inputData.leftHeld = false;
				break;
			case SDLK_s:
				inputData.saveHeld = false;
				inputData.downHeld = false;
				break;
			case SDLK_d:
				inputData.rightHeld = false;
				break;
			}
		}
	
		else if (event.type == SDL_MOUSEBUTTONDOWN && event.key.repeat == 0) {
			switch (event.button.button)
			case SDL_BUTTON_LEFT:
				inputData.mouseHeld = true;
				break;
		}
		else if (event.type == SDL_MOUSEBUTTONUP && event.key.repeat == 0) {
			switch (event.button.button)
			case SDL_BUTTON_LEFT:
				inputData.mouseHeld = false;
				break;
			
		}
		else if (event.type == SDL_MOUSEMOTION && event.key.repeat == 0) {
			inputData.mouseX = event.button.x;
			inputData.mouseY = event.button.y;
		}	
	}
	// poll each time
	inputData.mouseX = event.button.x;
	inputData.mouseY = event.button.y;
}

InputData Input::getData() {
	return inputData;
}

void Input::reset() {
	inputData.saveHeldPreviously = inputData.saveHeld;
	//inputData.player = false;
	//inputData.solid = false;
	//inputData.damage = false;
	//inputData.air = false;
}