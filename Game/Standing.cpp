#include "Standing.h"
#include "Helpers.h"
#include "Hero.h"

// other states used
#include "Walking.h"
#include "Jumping.h"
#include "Falling.h"

void Standing::enter(Hero& hero) {
	hero.resetAirJumps();

	hero.setAnimation(Animations::Hero_Standing);
	//std::cout << "Standing" << std::endl;
}

void Standing::exit(Hero& hero) {

}

void Standing::handleInput(Hero& hero, const InputData& data) {
	if (data.jumpHeld && !data.jumpHeldPreviously) {
		hero.groundJump();
	}
	if (data.leftHeld) {
		hero.goLeft(data.runHeld);
	}
	else if (data.rightHeld) {
		hero.goRight(data.runHeld);
	}
}

void Standing::update(Hero& hero) {
	if (hero.getYVelocity() < 0) {
		hero.changeState(new Jumping);
	}
	else if (hero.getYVelocity() > 0) {
		hero.changeState(new Falling);
	}
	else if (hero.getXVelocity() != 0) {
		hero.changeState(new Walking);
	}
}