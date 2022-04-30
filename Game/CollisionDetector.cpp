#include "CollisionDetector.h"

bool CollisionDetector::checkCollision(SDL_Rect hitBoxA, Position positionA, SDL_Rect hitBoxB, Position positionB) {
	float aLeft = positionA.x;
	float aRight = positionA.x + (float)hitBoxA.w; 
	float aTop = positionA.y;
	float aBottom = positionA.y + (float)hitBoxA.h;

	float bLeft = positionB.x;
	float bRight = positionB.x + (float)hitBoxB.w;
	float bTop = positionB.y;
	float bBottom = positionB.y + (float)hitBoxB.h;

	// check the conditions in which it would be impossible to collide
	if (aBottom <= bTop) {
		return false;
	}
	if (aTop >= bBottom) {
		return false;
	}
	if (aRight <= bLeft) {
		return false;
	}
	if (aLeft >= bRight) {
		return false;
	}

	// if all conditions fail, it is colliding
	return true;
}

// doesn't work right...
bool CollisionDetector::checkCollision(SDL_Rect hitBoxA, SDL_Rect hitBoxB) {
	int aLeft = hitBoxA.x;
	int aRight = hitBoxA.x + hitBoxA.w;
	int aTop = hitBoxA.y;
	int aBottom = hitBoxA.y + hitBoxA.h;

	int bLeft = hitBoxB.x;
	int bRight = hitBoxB.x + hitBoxB.w;
	int bTop = hitBoxB.y;
	int bBottom = hitBoxB.y + hitBoxB.h;

	// check the conditions in which it would be impossible to collide
	if (aBottom <= bTop) {
		return false;
	}
	if (aTop >= bBottom) {
		return false;
	}
	if (aRight <= bLeft) {
		return false;
	}
	if (aLeft >= bRight) {
		return false;
	}

	// if all conditions fail, it is colliding
	return true;
}