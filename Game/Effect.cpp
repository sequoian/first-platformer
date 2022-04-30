#include "Effect.h"

Effect::Effect(int id, Position position, SDL_Texture* texture, Animator animator, SDL_RendererFlip flipInfo, Animations animation, SDL_Rect* clip) :
Entity(id, position, texture, clip),
animator_(animator) 
{
	features_.isPlayer = false;
	features_.canCollide = false;
	features_.isPlatform = false;

	flipInfo_ = flipInfo;

	animator_.setAnimation(animation);
	animation_ = animation;

}

void Effect::update() {
	if (!animator_.isFinished()) {
		animator_.update();
		clip_ = animator_.getCurrentFrame();
	}
	else {
		done_ = true;
	}

}

/*
void Effect::setAnimation(Animations anim) {
	// TODO
	// make more generic (set animation funciton)
	animator_.setAnimation(anim);
}
*/

RenderData Effect::getRenderData() {
	RenderData data;
	data.texture = spriteSheet_;

	data.source = &clip_;
	//data.source = spriteClip_;
	//data.destination = renderBox_.get();

	data.destination = renderBox_;

	data.flip = flipInfo_;
	return data;
}

Effect* Effect::clone(Position position, SDL_RendererFlip flipInfo) {
	return new Effect(id_, position, spriteSheet_, animator_,flipInfo, animation_);
}