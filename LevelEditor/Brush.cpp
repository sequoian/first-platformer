#include "Brush.h"

void Brush::init(Cursor* cursor, Entity entity, SDL_Texture* texture, SDL_Rect clip) {
	cursor_ = cursor;
	entity_ = entity;
	texture_ = texture;
	clip_ = clip;
}