#include "Interpolator.h"

Interpolator::Interpolator() {
	remainder_ = 1.0;
}

Interpolator Interpolator::getInstance() {
	static Interpolator instance;
	return instance;
}

void Interpolator::setRemainder(float value) {
	remainder_ = value;
}

SDL_Rect Interpolator::interpolatePosition(SDL_Rect currentBox, SDL_Rect previousBox) {
	SDL_Rect interpolatedBox;
	interpolatedBox.x = calculate((float)currentBox.x, (float)previousBox.x);
	interpolatedBox.y = calculate((float)currentBox.y, (float)previousBox.y);
	return interpolatedBox;
}

float Interpolator::calculate(float current, float previous) {
	return current * remainder_ + previous * (1.0 - remainder_);
}