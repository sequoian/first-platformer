#include "CollisionHandler.h"
#include <cstdlib>

void CollisionHandler::handleCollisions(Entity* entity) {
	searchForCollisions(entity);
}

void CollisionHandler::addCollidableObject(Entity* entity) {
	collidableObjects_.push_back(entity);
}

void CollisionHandler::searchForCollisions(Entity* entity) {
	for (int i = 0; i < collidableObjects_.size(); ++i) {
		testForCollision(entity, collidableObjects_[i]);
	}
}

/*
void CollisionHandler::testForCollision(Entity* A, Entity* B) {


	// hack testing for wall collisions
	SDL_Rect rA = *A->getRenderData().destination;


	Position pos;
	pos.y = (rA.y + (rA.h / 2));
	pos.x = (rA.x + rA.w + 1);
	rA.w = 1;
	rA.h = 1;

	SDL_Rect coxB = *B->getRenderData().destination;

	if (detector_.checkCollision(rA, pos, coxB, B->getPosition())) {
		if (B->getFeatures().canCollide && !B->getFeatures().isPlayer) {
			A->collisions_.wall = true;
			A->collisions_.wallRight = true;
		}
	}

	/////

	SDL_Rect lA = *A->getRenderData().destination;


	//Position pos;
	pos.y = (lA.y + (lA.h /2));
	pos.x = (lA.x - 1);
	lA.w = 1;
	lA.h = 1;


	if (detector_.checkCollision(lA, pos, coxB, B->getPosition())) {
		if (B->getFeatures().canCollide && !B->getFeatures().isPlayer) {
			A->collisions_.wall = true;
			A->collisions_.wallLeft = true;
		}

	}


	// getting renderbox
	SDL_Rect* boxA = A->getRenderData().destination;
	SDL_Rect* boxB = B->getRenderData().destination;



	if (detector_.checkCollision(*boxA, A->getPosition(), *boxB, B->getPosition())) {
		resolveCollision(A, B);
	}
}
*/


void CollisionHandler::testForCollision(Entity* A, Entity* B) {




	/*
	// getting renderbox
	SDL_Rect* boxA = A->getRenderData().destination;
	SDL_Rect* boxB = B->getRenderData().destination;



	if (detector_.checkCollision(*boxA, A->getPosition(), *boxB, B->getPosition())) {
		resolveCollision(A, B);
	}
	*/

	
	// getting renderbox
	SDL_Rect boxA = A->getHitbox();
	SDL_Rect boxB = B->getHitbox();

	Position posA = A->getHitboxPos();
	Position posB = B->getHitboxPos();

	if (detector_.checkCollision(boxA, posA, boxB, posB)) {
		resolveCollision(A, B);
	}



	// hack testing for wall collisions
	SDL_Rect rA = *A->getRenderData().destination;


	Position pos;
	pos.y = rA.y;//(rA.y + (rA.h / 2));
	pos.x = (rA.x + rA.w + 1);
	rA.w = 1;
	//rA.h = 1;

	SDL_Rect coxB = *B->getRenderData().destination;

	if (detector_.checkCollision(rA, pos, coxB, B->getPosition())) {
		EntityFeatures features = B->getFeatures();
		if (features.canCollide && !features.isPlayer && features.isPlatform) {
			A->collisions_.wall = true;
			A->collisions_.wallRight = true;
		}
	}

	/////

	SDL_Rect lA = *A->getRenderData().destination;


	//Position pos;
	pos.y = lA.y;//(lA.y + (lA.h / 2));
	pos.x = (lA.x - 1);
	lA.w = 1;
	//lA.h = 1;


	if (detector_.checkCollision(lA, pos, coxB, B->getPosition())) {
		EntityFeatures features = B->getFeatures();
		if (features.canCollide && !features.isPlayer && features.isPlatform) {
			A->collisions_.wall = true;
			A->collisions_.wallLeft = true;
		}

	}
	
}

void CollisionHandler::resolveCollision(Entity* A, Entity* B) {
	A->onCollide(B);
	B->onCollide(A);
}