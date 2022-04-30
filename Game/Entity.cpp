#include "Entity.h"

Entity::Entity(int id, Position position, SDL_Texture* texture, SDL_Rect* clip) {
	
	id_ = id;
	position_ = position;
	previousPosition_ = position;
	spriteSheet_ = texture;

	//renderBox_ = std::unique_ptr<SDL_Rect>(new SDL_Rect);
	//spriteClip_ = std::unique_ptr<SDL_Rect>(new SDL_Rect);

	renderBox_ = new SDL_Rect;
	renderBox_->x = (int)position.x;
	renderBox_->y = (int)position.y;
	renderBox_->h = 20;
	renderBox_->w = 20;

	spriteClip_ = clip;

	flipInfo_ = SDL_FLIP_NONE;

	setHitbox();

	xVelocity_ = 0;
	yVelocity_ = 0;

	done_ = false;
	dead_ = false;
	victory_ = false;
}

// TODO
// delete these boxes
Entity::~Entity() {
	delete renderBox_;
	delete spriteClip_;
}

RenderData Entity::getRenderData() {
	RenderData data;
	data.texture = spriteSheet_;

	data.source = spriteClip_;
	data.destination = renderBox_;

	data.flip = flipInfo_;
	return data;
}

int Entity::getID() const {
	return id_;
}

EntityFeatures Entity::getFeatures() const {
	return features_;
}

int Entity::getXVelocity() const {
	return xVelocity_;
}

int Entity::getYVelocity() const {
	return yVelocity_;
}

void Entity::applyVelocity(int xVelocity, int yVelocity, float timeStep) {
	float xChange = (float)xVelocity * 1/timeStep;
	float yChange = (float)yVelocity * 1/timeStep;
	updatePosition(xChange, yChange);
}

void Entity::gravitate(int gravity) {
	yVelocity_ += gravity * gravityEffect_;
}

void Entity::updatePosition(float xChange, float yChange) {
	position_.x += xChange;
	position_.y += yChange;
	updateBoxes();
	setDirectionLastMoved(xChange, yChange);
	previousPosition_.x = position_.x;
	previousPosition_.y = position_.y;

}

void Entity::updateBoxes() {
	int xChange = (int)position_.x - (int)previousPosition_.x;
	int yChange = (int)position_.y - (int)previousPosition_.y;

	float xChangef = position_.x - previousPosition_.x;
	float yChangef = position_.y - previousPosition_.y;
 

	//float xChange = position_.x - previousPosition_.x;
	//float yChange = position_.y - previousPosition_.y;

	//renderBox_->x += (int)xChange;
	//renderBox_->y += (int)yChange;

	hitBoxPos_.x = position_.x + hitBoxXoffset_;
	hitBoxPos_.y = position_.y + hitBoxYoffset_;

	hitBox_.x += xChange;
	hitBox_.y += yChange;

	//hitBoxPos_.x += xChange;
	//hitBoxPos_.y += xChange;


	renderBox_->x += xChange;
	renderBox_->y += yChange;
}

void Entity::setDirectionLastMoved(float xChange, float yChange) {
	if (xChange != 0) {
		if (xChange < 0) {
			directionLastMoved_ = Direction_Left;
		}
		else {
			directionLastMoved_ = Direction_Right;
		}
	}
	else if (yChange != 0) {
		if (yChange < 0) {
			directionLastMoved_ = Direction_Up;
		}
		else
			directionLastMoved_ = Direction_Down;
	}
}

void Entity::setPosition(float x, float y) {
	position_.x = x;
	position_.y = y;
	updateBoxes();
	previousPosition_.x = position_.x;
	previousPosition_.y = position_.y;
}

void Entity::block(Entity* entity) {

	//static int x = 0;
	//std::cout << "blocked! " << x << std::endl;
	//x++;

	// using renderbox now as don't currently have hitbox
	//entity->getBlocked(*renderBox_);
	entity->getBlocked(hitBox_);
}

void Entity::getBlocked(SDL_Rect obstacle) {
	if (directionLastMoved_ == Direction_Down) {
		setPosition(position_.x, obstacle.y - renderBox_->h);
		yVelocity_ = 0;
		collisions_.floor = true;
	}
	else if (directionLastMoved_ == Direction_Right) {
		setPosition(obstacle.x - renderBox_->w, position_.y);
		xVelocity_ = 0;
		collisions_.wall = true;
		collisions_.wallRight = true;
	}
	else if (directionLastMoved_ == Direction_Left) {
		setPosition(obstacle.x + obstacle.w, position_.y);
		xVelocity_ = 0;
		collisions_.wall = true;
		collisions_.wallLeft = true;
	}
	else if (directionLastMoved_ == Direction_Up) {
		setPosition(position_.x, obstacle.y + obstacle.h);
		yVelocity_ = 0;
		collisions_.roof = true;
	}
}

Position Entity::getPosition() const {
	return position_;
}

void Entity::kill(Entity* entity) {
	entity->die();
}

void Entity::die() {
	if (!dead_) {
		dead_ = true;
		died_ = true;
	}

}

SDL_Rect Entity::getHitbox() const {
	return hitBox_;
}

Position Entity::getHitboxPos() const {
	return hitBoxPos_;
}

// To be called after renderbox is set up
void Entity::setHitbox() {
	hitBoxXoffset_ = 0;
	hitBoxYoffset_ = 0;

	hitBox_.x = renderBox_->x + hitBoxXoffset_;
	hitBox_.y = renderBox_->y + hitBoxYoffset_;
	hitBox_.w = renderBox_->w;
	hitBox_.h = renderBox_->h;

	hitBoxPos_ = position_;
}