#include "Falling.h"
#include "Helpers.h"
#include "Hero.h"

#include "Jumping.h"
#include "Standing.h"
#include "Walking.h"
#include "Running.h"
#include "WallClinging.h"

void Falling::enter(Hero& hero) {
	//std::cout << "Falling" << std::endl;
	hero.setAnimation(Animations::Hero_Falling);
}

void Falling::exit(Hero& hero) {

}

void Falling::handleInput(Hero& hero, const InputData& data) {
	if (data.jumpHeld) {
		//if (!data.jumpHeldPreviously && hero.getAirJumps() > 0) {
		//	hero.airJump();
		//}
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

void Falling::update(Hero& hero) {
	
	if (hero.getCollisions().floor) {
		if (hero.getXVelocity() == 0) {
			hero.changeState(new Standing);
		}
		else if (abs(hero.getXVelocity()) < hero.getRunThreshold()) {
			hero.changeState(new Walking);
		}
		else if (abs(hero.getXVelocity()) > hero.getRunThreshold()) {
			hero.changeState(new Running);
		}
	}
	else if (hero.getCollisions().wall) {
		hero.changeState(new WallClinging);
	}
	else if (hero.getYVelocity() <= 0) {
		hero.changeState(new Jumping);
	}

}