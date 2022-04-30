#ifndef ANIMATION_H_INCLUDED
#define ANIMATION_H_INCLUDED

//#include <map>
#include <vector>
#include <SDL.h>
#include "Helpers.h"

/*

My initial plan what to keep track of the current frame by having a iterator point to it.  However, defining
the iterator would, for some reason, corrupt the data in the SDL_Rect.  This caused my 3-4 hours of torturous
debugging, and I STILL don't know why it happended!!!  If I could figure it out, that would be great, but until
then I'll keep using currentFrameIndex to access the frame I want.

*/

class Animation {
public:
	Animation() {};
	//Animation(std::map<int, SDL_Rect> frames, bool looping);
	Animation(std::vector<Frame> frames, bool looping);
	SDL_Rect getFrame();
	bool update(int timePassed);
	void enter();
	bool isFinished() const {
		return finished_;
	}

private:
	// in a fit of stupidity, instead of using this Frame struct, I used a map.  Please remember what maps are for.
	std::vector<Frame> frames_;
	int currentFrameIndex_;
	bool isLooping_;
	bool finished_;

	bool nextFrame(int timePassed);
};

#endif