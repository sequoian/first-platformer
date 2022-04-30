#ifndef BRUSH_H
#define BRUSH_H


#include <SDL.h>
#include "Helpers.h"
class Cursor;

class Brush {
public:
	virtual ~Brush() {};
	virtual void input(InputData data) = 0;
	virtual void init(Cursor* cursor, Entity entity, SDL_Texture* texture, SDL_Rect clip);
protected:
	Cursor* cursor_;
	Entity entity_;
	SDL_Texture* texture_;
	SDL_Rect clip_;

};

#endif