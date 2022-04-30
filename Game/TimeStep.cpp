#include "TimeStep.h"

TimeStep::TimeStep(int minFPS, int maxFPS) {
	maxFramesPerSecond_ = maxFPS;
	minFramesPerSecond_ = minFPS;
	timePerUpdate_ = msPerSecond / maxFramesPerSecond_;
	maxElapsedTime_ = msPerSecond / minFramesPerSecond_;
	accumulatedTime_ = 0;
	looped_ = false;
}

bool TimeStep::canUpdate() {
	if (!looped_) {
		setup();
	}

	if (accumulatedTime_ >= timePerUpdate_) {
		update();
		return true;
	}
	else {
		skip();
		return false;
	}
}

// get data used by interpolator
float TimeStep::getRemainder() {
	return accumulatedTime_ / timePerUpdate_;
}

void TimeStep::setup() {
	accumulatedTime_ += getElapsedTime();
}

void TimeStep::update() {
	accumulatedTime_ -= timePerUpdate_;
	looped_ = true;
}

void TimeStep::skip() {
	looped_ = false;
}

Time TimeStep::getElapsedTime() {
	Time now = SDL_GetTicks();
	Time elapsedtime = now - timeLastUpdated_;
	timeLastUpdated_ = now;

	// cap elapsed itme to avoid too many loops
	if (elapsedtime > maxElapsedTime_) {
		elapsedtime = maxElapsedTime_;
	}
	return elapsedtime;
}