#ifndef ANIMATION_CACHE_H_INCLUDED
#define ANIMATION_CACHE_H_INCLUDED

#include "Animator.h"
#include "Helpers.h"
#include <map>

class AnimationCache {
public:
	enum Package {Hero, HeroDeath, HeroSpawn, HeroVictory};
	AnimationCache();
	Animator getAnimator(Package package);
private:
	std::map<Package, Animator> animators_;
	void makeHero();
	void makeHeroDeath();
	void makeHeroSpawn();
	void makeHeroVictory();
};

#endif