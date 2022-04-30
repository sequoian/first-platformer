#include "Running.h"
#include "Helpers.h"
#include "Hero.h"
#include "Jumping.h"
#include "Falling.h"
#include "Walking.h"
#include "Standing.h"


void Running::enter(Hero& hero) {
	hero.resetAirJumps();

	hero.setAnimation(Animations::Hero_Running);
	//std::cout << "Running" << std::endl;
}

void Running::exit(Hero& hero) {

}

void Running::handleInput(Hero& hero, const InputData& data) {
	if (data.jumpHeld && !data.jumpHeldPreviously) {
		hero.groundJump();
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

void Running::update(Hero& hero) {
	if (hero.getYVelocity() < 0) {
		hero.changeState(new Jumping);
	}
	else if (hero.getYVelocity() > 0) {
		hero.changeState(new Falling);
	}
	else if (abs(hero.getXVelocity()) < hero.getRunThreshold()) {
		hero.changeState(new Walking);
	}
	else if (hero.getXVelocity() == 0) {
		hero.changeState(new Standing);
	}
}