#include "Walking.h"
#include "Helpers.h"
#include "Hero.h"
#include "Jumping.h"
#include "Falling.h"
#include "Running.h"
#include "Standing.h"

void Walking::enter(Hero& hero) {
	hero.resetAirJumps();

	hero.setAnimation(Animations::Hero_Walking);

	//std::cout << "Walking" << std::endl;
}

void Walking::exit(Hero& hero) {

}

void Walking::handleInput(Hero& hero, const InputData& data) {
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

void Walking::update(Hero& hero) {
	if (hero.getYVelocity() < 0) {
		hero.changeState(new Jumping);
	}
	else if (hero.getYVelocity() > 0) {
		hero.changeState(new Falling);
	}
	else if (abs(hero.getXVelocity()) >= hero.getRunThreshold()) {
		hero.changeState(new Running);
	}
	else if (hero.getXVelocity() == 0) {
		hero.changeState(new Standing);
	}
}