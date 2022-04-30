#ifndef ANIMATOR_H_INCLUDED
#define ANIMATOR_H_INCLUDED

#include <SDL.h>
#include <map>
#include <vector>
#include "Animation.h"
#include "Helpers.h"
#include "Timer.h"


class Animator {
public:
	Animator(std::map<Animations, Animation> package);
	//Animator();
	bool update();
	void setAnimation(Animations animation);
	SDL_Rect getCurrentFrame();
	void setTimer(Timer& timer);
	bool isFinished() const {
		return currentAnimation_->isFinished();
	}
private:
	//std::map<HeroAnimation, Animation> animations_;
	std::map<Animations, Animation> animations_;
	Animation* currentAnimation_;
	Timer* timer_;
	Time timeLastChanged_;


	Time checkElapsedTime();
};

#endif