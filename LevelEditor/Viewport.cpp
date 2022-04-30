#include "Viewport.h"

Viewport::Viewport() {
	view_.x = 0;
	view_.y = 0;
	view_.w = 800;
	view_.h = 600;

	xVelocity_ = 0;
	yVelocity_ = 0;
}

Viewport::Viewport(SDL_Rect stage) {
	view_.x = 0;
	view_.y = 0;
	view_.w = 800;
	view_.h = 600;

	stage_ = stage;

	xVelocity_ = 0;
	yVelocity_ = 0;
}
/*
void Viewport::handleInput(InputData input) {
	if (input.leftHeld || input.rightHeld || input.upHeld || input.downHeld) {
		if (input.leftHeld) {
			goLeft();
		}
		else if (input.rightHeld) {
			goRight();
		}
		if (input.upHeld) {
			goUp();
		}
		else if (input.downHeld) {
			goDown();
		}
	}
	if (input.leftHeld) {
		goLeft();
	}
	else if (input.rightHeld) {
		goRight();
	}
	else if (input.upHeld) {
		goUp();
	}
	else if (input.downHeld) {
		goDown();
	}
	else {
		slowToStop();
	}
}
*/

void Viewport::handleInput(InputData input) {
	if (input.leftHeld) {
		goLeft();
	}
	else {
		slowLeft(0);
	}
	if (input.rightHeld) {
		goRight();
	}
	else {
		slowRight(0);
	}
	if (input.upHeld) {
		goUp();
	}
	else {
		slowUp(0);
	}
	if (input.downHeld) {
		goDown();
	}
	else {
		slowDown(0);
	}
}

void Viewport::update() {

	view_.x += xVelocity_;
	view_.y += yVelocity_;
}

void Viewport::modify(SDL_Rect& renderBox) {
	renderBox.x -= view_.x;
	renderBox.y -= view_.y;
}

void Viewport::modifyMouse(SDL_Rect& renderBox) {
	renderBox.x += view_.x;
	renderBox.y += view_.y;
}

bool Viewport::isInView(SDL_Rect renderBox) {
	if (detector_.checkCollision(view_, renderBox)) {
		return true;
	}
	else {
		return false;
	}
}

void Viewport::collideWithStage() {
	if (view_.x < stage_.x) {
		view_.x = stage_.x;
	}
	else if ((view_.x + view_.w) > (stage_.x + stage_.w)) {
		view_.x = (stage_.x + stage_.w) - view_.w;
	}
	if (view_.y < stage_.y) {
		view_.y = stage_.y;
	}
	else if ((view_.y + view_.h > stage_.x + stage_.h)) {
		view_.y = (stage_.y + stage_.h) - view_.h;
	}
}

void Viewport::goLeft() {

	if (xVelocity_ > -maxVelocity_) {
		xVelocity_ += -acceleration_;
	}
	else if (xVelocity_ < -maxVelocity_) {
		slowLeft(-maxVelocity_);
	}
}

void Viewport::goRight() {

		if (xVelocity_ < maxVelocity_) {
			xVelocity_ += acceleration_;
		}
		else if (xVelocity_ > maxVelocity_) {
			slowRight(maxVelocity_);
		}

}

void Viewport::goUp() {
	if (yVelocity_ > -maxVelocity_) {
		yVelocity_ += -acceleration_;
	}
	else if (yVelocity_ < -maxVelocity_) {
		slowUp(-maxVelocity_);
	}
}

void Viewport::goDown() {
	if (yVelocity_ < maxVelocity_) {
		yVelocity_ += acceleration_;
	}
	else if (yVelocity_ > maxVelocity_) {
		slowDown(maxVelocity_);
	}
}

void Viewport::slowLeft(int targetVelocity) {
	int deceleration = deceleration_;

	if (xVelocity_ < targetVelocity) {
		xVelocity_ -= -deceleration;
		if (xVelocity_ > targetVelocity) {
			xVelocity_ = targetVelocity;
		}
	}
}

void Viewport::slowRight(int targetVelocity) {
	int deceleration = deceleration_;

	if (xVelocity_ > targetVelocity) {
		xVelocity_ -= deceleration;
		if (xVelocity_ < targetVelocity) {
			xVelocity_ = targetVelocity;
		}
	}
}

void Viewport::slowDown(int targetVelocity) {
	int deceleration = deceleration_;

	if (yVelocity_ > targetVelocity) {
		yVelocity_ -= deceleration;
		if (yVelocity_ < targetVelocity) {
			yVelocity_ = targetVelocity;
		}
	}
}

void Viewport::slowUp(int targetVelocity) {
	int deceleration = deceleration_;

	if (yVelocity_ < targetVelocity) {
		yVelocity_ -= -deceleration;
		if (yVelocity_ > targetVelocity) {
			yVelocity_ = targetVelocity;
		}
	}
}

void Viewport::slowToStop() {
	if (xVelocity_ < 0) {
		slowLeft(0);
	}
	else if (xVelocity_ > 0) {
		slowRight(0);
	}
	else if (yVelocity_ < 0) {
		slowUp(0);
	}
	else if (yVelocity_ > 0) {
		slowDown(0);
	}
}