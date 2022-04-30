#include "Hero.h"

Hero::Hero(int id, Position position, SDL_Texture* texture, AudioPlayer* audio, 
	Animator animator, Effect* deathEffect, Effect* spawnEffect, Effect* victoryEffect, GameState* gameState, 
	Timer* timer, SDL_Rect* clip) :
  Entity(id, position, texture, clip),
  timer_(timer),
  animator_(animator),
  stateMachine_(*this)
  //,deathEffect_(deathEffect)
{
	features_.isPlayer = true;
	features_.canCollide = true;
	features_.isPlatform = false;
	audioPlayer_ = audio;

	spawnPoint_ = position;

	died_ = false;
	gameState_ = gameState;

	deathEffect_ = deathEffect;
	//deathEffect_->setAnimation(Animations::HeroDeath);
	spawnEffect_ = spawnEffect;
	//spawnEffect_->setAnimation(Animations::Hero_Spawning);
	victoryEffect_ = victoryEffect;
	//victoryEffect_->setAnimation(Animations::Hero_Victory);

	stateMachine_.enterFirstState();

	
	// test
	//clip_ = animator_.getCurrentFrame();
}

Hero::~Hero() {
	//std::cout << "AAAAHHH" << std::endl;
	delete deathEffect_;
	delete spawnEffect_;
	delete victoryEffect_;
}

/*
void Hero::move(Direction direction) {
	switch (direction) {
	case Direction_Left:
		goLeft();
		break;
	case Direction_Right:
		goRight();
		break;
	case Direction_None:
		slowToStop();
		break;
	}
}
*/

void Hero::onCollide(Entity* entity) {
	// because pure virtual
}

void Hero::handleInput(InputData data) {
	stateMachine_.handleInput(*this, data);
	resetCollisions();
}

/*
TODO
I gave hero it's own getRenderData function when I was testing the animations.  Having the sprite clip
be a pointer was fucking things up, I think.  It would probably be better to make the Entity sprite clip not
a pointer too, and perhaps consolidate the functions.

*/

RenderData Hero::getRenderData() {
	RenderData data;
	data.texture = spriteSheet_;

	data.source = &clip_;
	//data.source = spriteClip_;
	//data.destination = renderBox_.get();

	data.destination = renderBox_;

	data.flip = flipInfo_;
	return data;
}

void Hero::update() {
	// update state
	stateMachine_.update(*this);

	
	// update animation
	/*
	TODO
	I wanted to make it so that the clip would not be updated unless there was a frame change.
	It wasn't working out the way I expected and I got too tired to figure it out.
	I'll figure it out later.  Right now, it just updates the clip every frame.
	*/
	animator_.update();
	clip_ = animator_.getCurrentFrame();
	/*
	if (animator_.update()) {
		clip_ = animator_.getCurrentFrame();
	}
	*/
	
	//std::cout << position_.x << "," << position_.y << " : " << renderBox_->x << "," << renderBox_->y << std::endl;
}

void Hero::goLeft(bool runHeld) {
	if (runHeld) {
		if (xVelocity_ > -runMaxVelocity_) {
			xVelocity_ += -runAcceleration_;
		}
		else if (xVelocity_ < -runMaxVelocity_) {
			slowLeft(-runMaxVelocity_);
		}
	}
	else {
		if (xVelocity_ > -walkMaxVelocity_) {
			xVelocity_ += -walkAcceleration_;
		}
		else if (xVelocity_ < -walkMaxVelocity_) {
			slowLeft(-walkMaxVelocity_);
		}
	}
	flip(Direction_Left);
}

void Hero::goRight(bool runHeld) {
	if (runHeld) {
		if (xVelocity_ < runMaxVelocity_) {
			xVelocity_ += runAcceleration_;
		}
		else if (xVelocity_ > runMaxVelocity_) {
			slowRight(runMaxVelocity_);
		}
	}
	else {
		if (xVelocity_ < walkMaxVelocity_) {
			xVelocity_ += walkAcceleration_;
		}
		else if (xVelocity_ > walkMaxVelocity_) {
			slowRight(walkMaxVelocity_);
		}
	}
	flip(Direction_Right);

}

void Hero::slowLeft(int targetVelocity) {
	int deceleration;
	if (collisions_.floor) {
		deceleration = groundDeceleration_;
	}
	else {
		deceleration = airDeceleration_;
	}

	if (xVelocity_ < targetVelocity) {
		xVelocity_ -= -deceleration;
		if (xVelocity_ > targetVelocity) {
			xVelocity_ = targetVelocity;
		}
	}
}

void Hero::slowRight(int targetVelocity) {
	int deceleration;
	if (collisions_.floor) {
		deceleration = groundDeceleration_;
	}
	else {
		deceleration = airDeceleration_;
	}

	if (xVelocity_ > targetVelocity) {
		xVelocity_ -= deceleration;
		if (xVelocity_ < targetVelocity) {
			xVelocity_ = targetVelocity;
		}
	}
}

void Hero::slowToStop() {
	if (xVelocity_ < 0) {
		slowLeft(0);
	}
	else if (xVelocity_ > 0) {
		slowRight(0);
	}
}

void Hero::changeState(PlayerState* state) {
	stateMachine_.changeState(state);
}

void Hero::groundJump() {
	yVelocity_ = 0;
	yVelocity_ -= groundJumpImpulse_;
	audioPlayer_->playSoundEffect(SoundEffect::Jump);

}

void Hero::airJump() {
	yVelocity_ = 0;
	yVelocity_ -= airJumpImpulse_;
	//xVelocity_ = 0;
	currentAirJumps_ -= 1;
	audioPlayer_->playSoundEffect(SoundEffect::Jump);
}

void Hero::wallJump(Direction direction) {
	yVelocity_ = 0;
	yVelocity_ -= wallJumpVerticalImpulse_;
	xVelocity_ = 0;
	if (direction == Direction_Left) {
		xVelocity_ += wallJumpHorizontalImpulse_;
	}
	else if (direction == Direction_Right) {
		xVelocity_ -= wallJumpHorizontalImpulse_;
	}
	audioPlayer_->playSoundEffect(SoundEffect::Jump);
}

void Hero::jumpHigher() {
	gravityEffect_ = jumpHoldModifier_;
}

CollisionData Hero::getCollisions() const {
	return collisions_;
}

int Hero::getRunThreshold() const {
	return walkMaxVelocity_ + 1;
}

int Hero::getAirJumpThreshold() const {
	return airJumpThreshold_;
}

int Hero::getAirJumps() const {
	return currentAirJumps_;
}

void Hero::resetAirJumps() {
	currentAirJumps_ = maxAirJumps_;
}

void Hero::respawn() {

	
	
	restart();

	gameState_->addEntity(spawnEffect_->clone(position_, flipInfo_));

}

void Hero::restart() {
	position_ = spawnPoint_;
	//dead_ = false;
	xVelocity_ = 0;
	yVelocity_ = 0;
}

void Hero::reset() {

	gravityEffect_ = 1;
	died_ = false;
}

void Hero::stickToWall(Direction direction) {
	if (direction == Direction_Left) {
		xVelocity_ -= 1;
	}
	else if (direction == Direction_Right) {
		xVelocity_ += 1;
	}
}

void Hero::resetCollisions() {
	collisions_.reset();
}

void Hero::gravitate(int gravity) {
	yVelocity_ += gravity_ * gravityEffect_;
	if (yVelocity_ > terminalVelocity_) {
		yVelocity_ = terminalVelocity_;
	}
}

void Hero::setAnimation(Animations animation) {
	animator_.setAnimation(animation);
}

void Hero::flip(Direction direction) {
	if (direction == Direction_Left) {		
		flipInfo_ = SDL_FLIP_HORIZONTAL;
	}
	else if (direction == Direction_Right) {
		flipInfo_ = SDL_FLIP_NONE;
	}
	else {
		// invalid flip
		assert(false);
	}
	// adding this could be tricky, based on nature of SDL_RendererFlip
	/*
	else if (direction == Direction_Up) {

	}
	else if (direction == Direction_Down) {

	}
	*/
}

void Hero::deathThroes() {
	//Direction direction = Direction_Left;
	//yVelocity_ = 0;
	//yVelocity_ -= wallJumpVerticalImpulse_;
	//xVelocity_ = 0;
	//if (direction == Direction_Left) {
	//	xVelocity_ += wallJumpHorizontalImpulse_;
	//}
	//else if (direction == Direction_Right) {
	//	xVelocity_ -= wallJumpHorizontalImpulse_;
	//}
	timeDead_ = timer_->getTime();
	audioPlayer_->playSoundEffect(SoundEffect::Death);
	gameState_->addEntity(deathEffect_->clone(position_, flipInfo_));

}

bool Hero::canRespawn() {
	Time elapsed = timer_->getTime() - timeDead_;
	if (elapsed >= 750) {
		return true;
	}
	else {
		return false;
	}
}

void Hero::victory() {
	gameState_->victory();
	gameState_->addEntity(victoryEffect_->clone(position_, flipInfo_));
	//hero.setAnimation(HeroAnimation::Victory);
}

void Hero::endStage() {
	gameState_->done_ = true;
}