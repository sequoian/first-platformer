#include "WallClinging.h"
#include "Helpers.h"
#include "Hero.h"

#include "Jumping.h"
#include "Falling.h"
#include "Standing.h"

void WallClinging::enter(Hero& hero) {
	if (hero.getCollisions().wallLeft) {
		wallDirection_ = Direction_Left;
	}
	else if (hero.getCollisions().wallRight) {
		wallDirection_ = Direction_Right;
	}

	hero.resetAirJumps();

	hero.setAnimation(Animations::Hero_Clinging);

	//std::cout << "Clinging" << std::endl;



}

void WallClinging::exit(Hero& hero) {
	if (wallDirection_ == Direction_Left) {
		if (hero.getXVelocity() <= 0) {
			//unstick(hero.getPosition());
		}
	}
	else if (wallDirection_ == Direction_Right) {
		if (hero.getXVelocity() >= 0) {
			//unstick(hero.getPosition());
		}
	}
}

void WallClinging::handleInput(Hero& hero, const InputData& data) {
	if (data.jumpHeld) {
		if (!data.jumpHeldPreviously) {
			hero.wallJump(wallDirection_);
		}
		else if (hero.getYVelocity() < 0) {
			hero.jumpHigher();
		}
	}
	if (data.leftHeld) {
		hero.goLeft(data.runHeld);
	}
	else if (data.rightHeld) {
		hero.goRight(data.runHeld);
	}

	//hero.stickToWall(wallDirection_);
}

void WallClinging::update(Hero& hero) {
	if (!hero.getCollisions().wall) {
		if (hero.getYVelocity() <= 0) {
			hero.changeState(new Jumping);
		}
		else {
			hero.changeState(new Falling);
		}
		
	}
	else if (hero.getCollisions().floor) {
		hero.changeState(new Standing);
	}


	// flip sprite
	// overrides goLeft/Right flips
	if (wallDirection_ == Direction_Left) {
		hero.flip(Direction_Right);
	}
	else if (wallDirection_ == Direction_Right) {
		hero.flip(Direction_Left);
	}

}
