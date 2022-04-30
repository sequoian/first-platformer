#include "Physics.h"

void Physics::affect(Entity* entity) {
	applyGravity(entity);
}

void Physics::applyGravity(Entity* entity) {
	entity->gravitate(gravityForce_);
}