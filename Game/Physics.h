#ifndef PHYSICS_H
#define PHYSICS_H

#include "Entity.h"

class Physics {
public:
	void affect(Entity* entity);
private:
	int gravityForce_ = 30;
	void applyGravity(Entity* entity);
};

#endif