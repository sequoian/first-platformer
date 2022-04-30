#include "Global.h"
#include "Helpers.h"
#include "Hero.h"
#include "Dead.h"
#include "Victory.h"

void Global::enter(Hero& hero) {

}

void Global::exit(Hero& hero) {

}

void Global::handleInput(Hero& hero, const InputData& data) {
	
}

void Global::update(Hero& hero) {
	if (hero.victory_) {
		hero.changeState(new Victory);
		hero.victory_ = false;
	}
	else if (hero.died_) {
		hero.changeState(new Dead);
	}
	// gravityEffect, collisions
	hero.reset();
}
