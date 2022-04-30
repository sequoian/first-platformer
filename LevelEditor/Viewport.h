#ifndef VIEWPORT_H_INCLUDED
#define VIEWPORT_H_INCLUDED

#include <SDL.h>
#include "CollisionDetector.h"
#include "Helpers.h"

class Viewport {
public:
	Viewport();
	Viewport(SDL_Rect stage);
	void handleInput(InputData input);
	void update();
	void modify(SDL_Rect& renderBox);
	void modifyMouse(SDL_Rect& renderBox);
	bool isInView(SDL_Rect renderBox);

private:
	CollisionDetector detector_;
	SDL_Rect view_;
	SDL_Rect stage_;
	int xVelocity_;
	int yVelocity_;
	const int maxVelocity_ = 10;
	const int acceleration_ = 5;
	const int deceleration_ = 5;

	void collideWithStage();
	void goLeft();
	void goRight();
	void goUp();
	void goDown();
	void slowLeft(int targetVelocity);
	void slowRight(int targetVelocity);
	void slowUp(int targetVelocity);
	void slowDown(int targetVelocity);
	void slowToStop();
};

#endif 
