#include "FramesPerSecond.h"
#include <SDL.h>

FramesPerSecond::FramesPerSecond() {
	setCap(-1);
}

FramesPerSecond::FramesPerSecond(int cap) {
	setCap(cap);
}

void FramesPerSecond::tick() {
	checkElapsedTime();
	if (fpsLimit_ > -1) {
		capFPS();
	}
	calculateFPS();
}

void FramesPerSecond::calculateFPS() {
	fps_ = (Time)msPerSecond / elapsedTime_;
}

void FramesPerSecond::capFPS() {
	if (elapsedTime_ < minimumElapsedTime_) {
		SDL_Delay(minimumElapsedTime_ - elapsedTime_);
	}
	elapsedTime_ += minimumElapsedTime_ - elapsedTime_;
	lastTick_ = SDL_GetTicks();
}

void FramesPerSecond::checkElapsedTime() {
	Time now = SDL_GetTicks();
	Time elapsedTime = now - lastTick_;
	if (elapsedTime <= 0) {
		elapsedTime = 1;
	}
	elapsedTime_ = elapsedTime;
	lastTick_ = now;
	//std::cout << elapsedTime_ << std::endl;
}
	
int FramesPerSecond::getCount() {
	return fps_;
}

void FramesPerSecond::setCap(int cap) {
	fpsLimit_ = cap;
	minimumElapsedTime_ = msPerSecond / fpsLimit_;
}