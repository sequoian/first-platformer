#include "AnimationCache.h"

AnimationCache::AnimationCache() {
	makeHero();
	makeHeroDeath();
	makeHeroSpawn();
	makeHeroVictory();
}

Animator AnimationCache::getAnimator(Package package) {
	return animators_.at(package);
}

void AnimationCache::makeHero() {

	// RedCube.png frames
	SDL_Rect stand = { 0, 0, 20, 20 };
	SDL_Rect step1 = { 20, 0, 20, 20 };
	SDL_Rect step2 = { 40, 0, 20, 20 };
	SDL_Rect jump = { 60, 0, 20, 20 };
	SDL_Rect fall = { 80, 0, 20, 20 };
	SDL_Rect cling = { 100, 0, 20, 20 };

	// animation package to be sent to animator
	std::map<Animations, Animation> package;

	// The indiviual animation to be inserted into the package
	std::vector<Frame> animation;

	/*
	Add all frames to the animation,
	add the animation to the package,
	then clear the animation container for the next animation
	*/

	// standing
	animation.emplace_back(Frame{ 0, stand });
	package.emplace(Animations::Hero_Standing, Animation(animation, false));
	animation.clear();

	// walking
	animation.emplace_back(Frame{ 500, stand });
	animation.emplace_back(Frame{ 500, step1 });
	animation.emplace_back(Frame{ 500, stand });
	animation.emplace_back(Frame{ 500, step2 });
	package.emplace(Animations::Hero_Walking, Animation(animation, true));
	animation.clear();

	// running
	animation.emplace_back(Frame{ 250, stand });
	animation.emplace_back(Frame{ 250, step1 });
	animation.emplace_back(Frame{ 250, stand });
	animation.emplace_back(Frame{ 250, step2 });
	package.emplace(Animations::Hero_Running, Animation(animation, true));
	animation.clear();

	// jumping
	animation.emplace_back(Frame{ 0, jump });
	package.emplace(Animations::Hero_Jumping, Animation(animation, false));
	animation.clear();

	// falling
	animation.emplace_back(Frame{ 0, fall });
	package.emplace(Animations::Hero_Falling, Animation(animation, false));
	animation.clear();

	// clinging
	animation.emplace_back(Frame{ 0, cling });
	package.emplace(Animations::Hero_Clinging, Animation(animation, false));
	animation.clear();

	// add final package to animators
	animators_.emplace(Package::Hero, Animator(package));
}


void AnimationCache::makeHeroDeath() {

	// Death.png frames
	SDL_Rect death1 = { 0, 0, 20, 20 };
	SDL_Rect death2 = { 20, 0, 20, 20 };
	SDL_Rect death3 = { 40, 0, 20, 20 };
	SDL_Rect death4 = { 60, 0, 20, 20 };

	std::map<Animations, Animation> package;
	std::vector<Frame> animation;

	// main
	animation.emplace_back(Frame{ 250, death1 });
	animation.emplace_back(Frame{ 80, death2 });
	animation.emplace_back(Frame{ 80, death3 });
	animation.emplace_back(Frame{ 80, death4 });
	package.emplace(Animations::HeroDeath, Animation(animation, false));
	animation.clear();

	// add final package to animators
	animators_.emplace(Package::HeroDeath, Animator(package));
}

void AnimationCache::makeHeroSpawn() {
	// Spawn.png frames
	SDL_Rect spawn1 = { 0, 0, 20, 20 };
	SDL_Rect spawn2 = { 20, 0, 20, 20 };
	SDL_Rect spawn3 = { 40, 0, 20, 20 };

	std::map<Animations, Animation> package;
	std::vector<Frame> animation;

	// main
	animation.emplace_back(Frame{ 50, spawn1 });
	animation.emplace_back(Frame{ 50, spawn2 });
	animation.emplace_back(Frame{ 50, spawn3 });
	package.emplace(Animations::Hero_Spawning, Animation(animation, false));
	animation.clear();

	// add final package to animators
	animators_.emplace(Package::HeroSpawn, Animator(package));
}

void AnimationCache::makeHeroVictory() {
	// Spawn.png frames
	SDL_Rect one = { 0, 0, 20, 20 };
	SDL_Rect two = { 20, 0, 20, 20 };
	SDL_Rect three = { 40, 0, 20, 20 };
	SDL_Rect four = { 60, 0, 20, 20 };
	SDL_Rect five = { 80, 0, 20, 20 };
	SDL_Rect six = { 100, 0, 20, 20 };
	SDL_Rect seven = { 120, 0, 20, 20 };

	std::map<Animations, Animation> package;
	std::vector<Frame> animation;

	// main
	animation.emplace_back(Frame{ 750, one });
	animation.emplace_back(Frame{ 80, two });
	animation.emplace_back(Frame{ 80, three });
	animation.emplace_back(Frame{ 80, four });
	animation.emplace_back(Frame{ 80, five });
	animation.emplace_back(Frame{ 80, six });
	animation.emplace_back(Frame{ 80, seven });
	package.emplace(Animations::Hero_Victory, Animation(animation, false));
	animation.clear();

	// add final package to animators
	animators_.emplace(Package::HeroVictory, Animator(package));
}