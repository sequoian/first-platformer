#include "Cell.h"

Cell::Cell(SDL_Rect spriteBox, SDL_Texture* texture, SDL_Rect clip, Entity entity) {
	spriteBox_ = spriteBox;
	texture_ = texture;
	clip_ = clip;
	type_ = entity;
}

void Cell::set(Entity entity, SDL_Texture* texture, SDL_Rect* clip) {
	type_ = entity;
	texture_ = texture;
	clip_ = *clip;
}

void Cell::set(int x, int y, Entity entity, SDL_Texture* texture, SDL_Rect* clip) {
	spriteBox_ = { x, y, 20, 20 };
	type_ = entity;
	texture_ = texture;
	clip_ = *clip;
	
}

void Cell::render(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, texture_, &clip_, &spriteBox_); 
}

void Cell::render(SDL_Renderer* renderer, Viewport viewport) {
	if (viewport.isInView(spriteBox_)) {

		SDL_Rect renderBox = spriteBox_;
		viewport.modify(renderBox);
		SDL_RenderCopy(renderer, texture_, &clip_, &renderBox);
	}
}

SDL_Rect Cell::getBox() {
	return spriteBox_;
}

FileData Cell::getFileData() {
	FileData data;
	data.x = spriteBox_.x;
	data.y = spriteBox_.y;
	data.entity = type_;
	return data;
}