#ifndef COLLISION_DETECTOR_H
#define COLLISION_DETECTOR_H

#include <SDL.h>
//#include "Helpers.h"

class CollisionDetector {
public:
	//bool checkCollision(SDL_Rect hitBoxA, Position positionA, SDL_Rect hitBoxB, Position positionB);
	bool checkCollision(SDL_Rect hitBoxA, SDL_Rect hitBoxB);
};

#endif