#include "Spawning.h"
#include "Hero.h"
//#include "Helpers.h"

#include "Falling.h"

void Spawning::enter(Hero& hero) {
	//hero.setAnimation(HeroAnimation::Spawning);
	//hero.respawn();
	done_ = false;
	spawnStart_ = hero.timer_->getTime();
	hero.respawn();

	//std::cout << "enter spawn" << std::endl;
}

void Spawning::exit(Hero& hero) {
	hero.dead_ = false;

	//std::cout << "exit spawn" << std::endl;
}

void Spawning::handleInput(Hero& hero, const InputData& data) {
	if (done_) {
		hero.changeState(new Falling);
	}
}

void Spawning::update(Hero& hero) {

	Time elapsed = hero.timer_->getTime() - spawnStart_;
	if (elapsed >= 150) {
		done_ = true;
	}
}
