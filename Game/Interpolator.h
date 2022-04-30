#ifndef INTERPOLATOR_H_INCLUDED
#define INTERPOLATOR_H_INCLUDED
#include <Sdl.h>

// Implemented as a singleton
class Interpolator {
public:
	static Interpolator getInstance();
	void setRemainder(float value);
	SDL_Rect interpolatePosition(SDL_Rect currentBox, SDL_Rect previousBox);
private:
	float remainder_;

	Interpolator();
	float calculate(float current, float previous);
};

#endif