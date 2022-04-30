#include "Animation.h"
#include <assert.h>

Animation::Animation(std::vector<Frame> frames, bool looping) {
	// no frames in animation
	if (frames.empty()) {
		assert(false);
	}
	frames_ = frames;
	isLooping_ = looping;
	finished_ = false;
	currentFrameIndex_ = 0;
}

SDL_Rect Animation::getFrame() {
	return frames_[currentFrameIndex_].clip;
}

bool Animation::update(int timePassed) {
	if (frames_.size() > 1) {
		return nextFrame(timePassed);
	}
	else {
		return false;
	}
}

void Animation::enter() {
	currentFrameIndex_ = 0;
}

bool Animation::nextFrame(int timePassed) {
	bool changedFrame = false;
	// animation is ready to change frames
	if (frames_[currentFrameIndex_].timeInFrame <= timePassed) {
		// has more frames to go
		if (currentFrameIndex_ < (frames_.size() - 1)) {
			++currentFrameIndex_;
			changedFrame = true;
		}
		// no more frames, but should loop
		else if (isLooping_) {
			currentFrameIndex_ = 0;
			changedFrame = true;
		}
		// no more frames and does not loop
		else {
			finished_ = true;
		}
	}
	return changedFrame;
}


// using an iterator (better?)
/*
bool Animation::nextFrame(int timePassed) {
	bool changedFrame = false;
	// animation is ready to change frames
	if (currentFrame_->timeInFrame <= timePassed) {
		// has more frames to go
		if (currentFrame_ != frames_.end()) {
			++currentFrame_;
			changedFrame = true;
		}
		// no more frames, but should loop
		else if (isLooping_) {
			currentFrame_ = frames_.begin();
			changedFrame = true;
		}		
	}
	return changedFrame;
}
*/