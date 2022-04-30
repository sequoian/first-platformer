#ifndef EFFECT_H_INCLUDED
#define EFFECT_H_INCLUDED

#include "Entity.h"
#include "Animator.h"

class Effect : public Entity {
public:
	Effect(int id, Position position, SDL_Texture* texture, Animator animator, SDL_RendererFlip flipInfo,
		Animations animation, SDL_Rect* clip = nullptr);
	void update();
	RenderData getRenderData();
	Effect* clone(Position position, SDL_RendererFlip flipInfo);
	//void setAnimation(Animations anim);
private:
	Animator animator_;
	SDL_Rect clip_;
	Animations animation_;

};

#endif