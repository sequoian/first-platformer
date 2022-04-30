#ifndef TIME_STEP_H_INCLUDED
#define TIME_STEP_H_INCLUDED

#include <SDL.h>
#include "Helpers.h"

class TimeStep {
public:
	TimeStep(int minFPS, int maxFPS);
	bool canUpdate();
	float getRemainder();
private:
	int maxFramesPerSecond_;
	int minFramesPerSecond_;
	Time timePerUpdate_;
	Time maxElapsedTime_;
	Time timeLastUpdated_;
	Time accumulatedTime_;
	bool looped_;

	void setup();
	void update();
	void skip();
	Time getElapsedTime();
};

#endif