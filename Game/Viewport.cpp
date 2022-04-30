#include "Viewport.h"


Viewport::Viewport() {
	view_.x = 0;
	view_.y = 0;
	view_.w = 800;
	view_.h = 600;

	//stage_ = stage;
}

void Viewport::setTarget(Entity& target) {
	target_ = &target;
}

void Viewport::setStage(SDL_Rect stage) {
	stage_ = stage;
}

void Viewport::update() {
	SDL_Rect targetData = *target_->getRenderData().destination;



	view_.x = targetData.x - (view_.w / 2);
	view_.y = targetData.y - (view_.h / 2);

	collideWithStage();
}

void Viewport::modify(SDL_Rect& renderBox) {
	renderBox.x -= view_.x;
	renderBox.y -= view_.y;
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