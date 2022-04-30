#ifndef ENTITY_H
#define ENTITY_H

#include <SDL.h>
#include <memory>
#include "Helpers.h"

class Entity {
public:
	Entity(int id, Position position, SDL_Texture* texture, SDL_Rect* clip);
	virtual ~Entity();
	void applyVelocity(int xVelocity, int yVelocity, float timeStep);
	void setPosition(float x, float y);
	virtual void gravitate(int gravity);

	virtual void handleInput(InputData data) {};
	virtual void update() {};
	virtual void onCollide(Entity* entity) {};


	// accessors
	int getID() const;
	Position getPosition() const;
	int getXVelocity() const;
	int getYVelocity() const;
	EntityFeatures getFeatures() const;
	SDL_Rect getHitbox() const;
	Position getHitboxPos() const;
	bool isDead() const { 
		return dead_; 
	};
	bool isDone() const {
		return done_;
	};

	// make const
	virtual RenderData getRenderData();


	// should be private/protected
	int xVelocity_;
	int yVelocity_;


	// should move to specific classes that need it
	CollisionData collisions_;
	bool died_;

	virtual void restart() {};

	bool victory_;
	bool dead_;


protected:
	int id_;
	Position position_;
	Position previousPosition_;
	float gravityEffect_ = 1.0;
	
	bool done_;
	SDL_Texture* spriteSheet_;
	SDL_RendererFlip flipInfo_;
	EntityFeatures features_;
	SDL_Rect hitBox_;
	Position hitBoxPos_;

	virtual void updatePosition(float xChange, float yChange);
	virtual void updateBoxes();
	virtual void setHitbox();

	// should not be pointers
	SDL_Rect* renderBox_;
	SDL_Rect* spriteClip_;

	// should move to specific classes that need it
	Direction directionLastMoved_;
	virtual void setDirectionLastMoved(float xChange, float yChange);
	
	virtual void block(Entity* entity);
	virtual void kill(Entity* entity);

	// move to perhaps another subclass / make pure(ish)
	virtual void getBlocked(SDL_Rect obstacle);
	virtual void die();

	// testing hitbox
	int hitBoxXoffset_;
	int hitBoxYoffset_;
};

#endif