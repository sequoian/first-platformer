#ifndef FRAMES_PER_SECOND_H
#define FRAMES_PER_SECOND_H

#include "Helpers.h"

class FramesPerSecond {
public:
	FramesPerSecond();
	FramesPerSecond(int cap);
	void tick();
	int getCount();
	void setCap(int cap);
private:
	int fps_;
	int fpsLimit_;
	Time minimumElapsedTime_;
	Time elapsedTime_;
	Time lastTick_;

	void checkElapsedTime();
	void calculateFPS();
	void capFPS();

};

#endif