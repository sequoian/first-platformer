#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

#include "Helpers.h"

class Timer {
public:
	Timer();
	void start();
	void stop();
	void pause();
	void unpause();
	Time getTime();
	bool isPaused();
	bool isStarted();
private:
	Time startTicks_;
	Time pauseTicks_;
	bool paused_;
	bool started_;
};

#endif