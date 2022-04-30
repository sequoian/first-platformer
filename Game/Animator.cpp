#include "Animator.h"
#include <assert.h>

Animator::Animator(std::map<Animations, Animation> package) {
	currentAnimation_ = nullptr;
	timer_ = nullptr;
	animations_ = package;
}

/*
Animator::Animator() {
	currentAnimation_ = nullptr;
	
	// TODO : Hard coding animations, better to use outside data
	// RedCube.png frames
	SDL_Rect stand = { 0, 0, 20, 20 };
	SDL_Rect step1 = { 20, 0, 20, 20 };
	SDL_Rect step2 = { 40, 0, 20, 20 };
	SDL_Rect jump = { 60, 0, 20, 20 };
	SDL_Rect fall = { 80, 0, 20, 20 };
	SDL_Rect cling = { 100, 0, 20, 20 };

	std::vector<Frame> frames;

	// standing
	// add all frames in the animation
	frames.emplace_back(Frame {0, stand}); 
	// add animation to container
	animations_.emplace(HeroAnimation::Standing, Animation(frames, false));
	// clear frame container for next animation
	frames.clear();

	// walking
	frames.emplace_back(Frame {500, stand}); 
	frames.emplace_back(Frame {500, step1}); 
	frames.emplace_back(Frame {500, stand}); 
	frames.emplace_back(Frame {500, step2}); 
	animations_.emplace(HeroAnimation::Walking, Animation(frames, true));
	frames.clear();

	// running
	frames.emplace_back(Frame{ 250, stand }); 
	frames.emplace_back(Frame{ 250, step1 });
	frames.emplace_back(Frame{ 250, stand });
	frames.emplace_back(Frame{ 250, step2 });
	animations_.emplace(HeroAnimation::Running, Animation(frames, true));
	frames.clear();

	// jumping
	frames.emplace_back(Frame {0, jump}); 
	animations_.emplace(HeroAnimation::Jumping, Animation(frames, false));
	frames.clear();

	// falling
	frames.emplace_back(Frame {0, fall}); 
	animations_.emplace(HeroAnimation::Falling, Animation(frames, false));
	frames.clear();

	// clinging
	frames.emplace_back(Frame {0, cling}); 
	animations_.emplace(HeroAnimation::Clinging, Animation(frames, false));
	frames.clear();

	

	setAnimation(HeroAnimation::Running);
}
*/

void Animator::setAnimation(Animations animation) {
	// change animation
	
	auto itr = animations_.find(animation);
	if (itr != animations_.end()) {
		currentAnimation_ = &itr->second;
		currentAnimation_->enter();
		timeLastChanged_ = timer_->getTime();
	}
	else {
		assert(false); // animation not found
	}

	currentAnimation_ = &animations_[animation];
	currentAnimation_->enter();	
}

/*
void Animator::setAnimation(HeroAnimation animation) {
	// change animation
	currentAnimation_ = &animations_[animation];
	currentAnimation_->enter();

	// reset timer fpr next frame
	lastCheck_ = SDL_GetTicks();
}
*/

SDL_Rect Animator::getCurrentFrame() {
	return currentAnimation_->getFrame();
}

bool Animator::update() {
	Time timeElapsed = checkElapsedTime();
	bool frameChanged;
	frameChanged = currentAnimation_->update(timeElapsed);

	// reset timer for next frame
	if (frameChanged) {
		timeLastChanged_ = timer_->getTime();
	}

	return frameChanged;
}

Time Animator::checkElapsedTime() {
	return timer_->getTime() - timeLastChanged_;
}

void Animator::setTimer(Timer& timer) {
	timer_ = &timer;
}