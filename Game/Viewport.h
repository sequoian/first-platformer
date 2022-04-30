#ifndef VIEWPORT_H_INCLUDED
#define VIEWPORT_H_INCLUDED

#include "Entity.h"
#include "CollisionDetector.h"

class Viewport {
public:
	Viewport();
	void setTarget(Entity& target);
	void update();
	void modify(SDL_Rect& renderBox);
	bool isInView(SDL_Rect renderBox);
	void setStage(SDL_Rect stage);

private:
	Entity* target_;
	CollisionDetector detector_;
	SDL_Rect view_;
	SDL_Rect stage_;

	void collideWithStage();
};

#endif 
