#include "Updater.h"

void Updater::update(Entity* entity) {

	physics_.affect(entity);

	// move along y axis
	entity->applyVelocity(0, entity->getYVelocity(), g_TimeStepFPS);

	if (!entity->isDead()) {
		collisionHandler_.handleCollisions(entity);
	}


	/* 
	TODO: because of the way I move one axis, then check collision, this is not always accurate.
	For example, when moving diagonally and just scraping by a corner, the y axis goes down first, touching
	the tile, whereas if it moved both axis' at once, calculating the path it goes in a straight line,
	it would slip by the tile by fractions of a pixel.
	I should move both axis at once for a more accurate simulations.
	At the moment, though, since I have not changed it yet, if I don't return after dying on the y axis step,
	the death animation occur (sometimes) off the damage tile, making it obvious how inaccurate it is.
	*/
	if (entity->isDead()) {
		return;
	}

	// move along x axis
	entity->applyVelocity(entity->getXVelocity(), 0, g_TimeStepFPS);

	if (!entity->isDead()) {
		collisionHandler_.handleCollisions(entity);
	}
}

void Updater::addCollidableObject(Entity* entity) {
	collisionHandler_.addCollidableObject(entity);
}