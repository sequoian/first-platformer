#include "Jumping.h"
#include "Helpers.h"
#include "Hero.h"

#include "WallClinging.h"
#include "Falling.h"



void Jumping::enter(Hero& hero) {
	//std::cout << "Jumping" << std::endl;

	hero.setAnimation(Animations::Hero_Jumping);
}

void Jumping::exit(Hero& hero) {

}

void Jumping::handleInput(Hero& hero, const InputData& data) {
	if (data.jumpHeld) {
		//if (!data.jumpHeldPreviously && hero.getAirJumps() > 0 && hero.getYVelocity() >= hero.getAirJumpThreshold()) {
		//	hero.airJump();
		//}
		//else 
		if (hero.getYVelocity() < 0) {
			hero.jumpHigher();
		}
	}
	if (data.leftHeld) {
		hero.goLeft(data.runHeld);
	}
	else if (data.rightHeld) {
		hero.goRight(data.runHeld);
	}
	else {
		hero.slowToStop();
	}
}

void Jumping::update(Hero& hero) {
	if (hero.getCollisions().wall) {
		hero.changeState(new WallClinging);
	}
	else if (hero.getYVelocity() >= 0) {
		hero.changeState(new Falling);
	}

}