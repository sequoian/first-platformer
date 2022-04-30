#ifndef UPDATER_H
#define UPDATER_H
#include "Entity.h"
#include "Physics.h"
#include "CollisionHandler.h"

class Updater {
public:
	void update(Entity* entity);
	void addCollidableObject(Entity* entity);
private:
	// in leiu of actually communicating with logic fps
	//const int logicFPS_ = 50;
	Physics physics_;
	CollisionHandler collisionHandler_;
};

#endif