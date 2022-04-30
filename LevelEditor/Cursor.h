#ifndef CURSOR_H
#define CURSOR_H

#include <map>
#include <SDL.h>
#include "Brush.h"
#include "Helpers.h"
#include "Canvas.h"
#include "SolidBrush.h"
#include "AirBrush.h"
#include "PlayerBrush.h"
#include "DamageBrush.h"
#include "GoalBrush.h"
#include "Viewport.h"

class Cursor {
public:
	Cursor(Canvas* canvas, SDL_Texture* texture);
	~Cursor();
	void input(InputData data);
	void input(InputData data, Viewport viewport);
	void draw(Entity entity, SDL_Texture* texture, SDL_Rect* clip);
	void setPosition(int x, int y);
	void changeBrush(Entity entity);
private:
	int x_;
	int y_;
	std::map<Entity, Brush*> brushes_;
	Brush* currentBrush_;
	Canvas* canvas_;

	void makeBrushes(SDL_Texture* texture);
	void destroyBrushes();
};

#endif