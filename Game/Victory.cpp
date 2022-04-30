#include "Victory.h"
#include "Hero.h"
#include "Helpers.h"
#include "Falling.h"
#include "Spawning.h"


void Victory::enter(Hero& hero) {
	//hero.setAnimation(HeroAnimation::Victory);
	//hero.deathThroes();
	hero.victory();
	//std::cout << "enter victory" << std::endl;
	hero.dead_ = true;
}

void Victory::exit(Hero& hero) {
	//std::cout << "exit victory" << std::endl;
}

void Victory::handleInput(Hero& hero, const InputData& data) {
	if (data.jumpHeld && !data.jumpHeldPreviously) {
		hero.endStage();
		return;
	}
	else if (data.restartHeld && !data.restartHeldPreviously) {
		hero.restart();
		//hero.changeState(new Falling);
		hero.changeState(new Spawning);
	}
}

void Victory::update(Hero& hero) {

}