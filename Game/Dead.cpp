#include "Dead.h"
#include "Hero.h"
#include "Helpers.h"

#include "Falling.h"
#include "Spawning.h"

void Dead::enter(Hero& hero) {
	//hero.setAnimation(HeroAnimation::Dead);
	hero.deathThroes();
	done_ = false;
}

void Dead::exit(Hero& hero) {
	//hero.respawn();
}

void Dead::handleInput(Hero& hero, const InputData& data) {
	bool forceRespawn = (data.jumpHeld && !data.jumpHeldPreviously);

	if (forceRespawn || done_) {
		//hero.changeState(new Falling);
		hero.changeState(new Spawning);
	}
}

void Dead::update(Hero& hero) {
	if (hero.canRespawn()) {
		done_ = true;
	}
}
