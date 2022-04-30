#ifndef COLLISION_HANDLER_H
#define COLLISION_HANDLER_H

#include <vector>
#include "CollisionDetector.h"
#include "Entity.h"

class CollisionHandler {
public:
	void handleCollisions(Entity* entity);
	void addCollidableObject(Entity* entity);
private:
	CollisionDetector detector_;
	std::vector<Entity*> collidableObjects_;

	void searchForCollisions(Entity* entity);
	void testForCollision(Entity* A, Entity* B);
	void resolveCollision(Entity* A, Entity* B);
};

#endif