#ifndef CELL_H
#define CELL_H

#include <SDL.h>
#include "Helpers.h"
#include "Viewport.h"

class Cell {
public:
	Cell(SDL_Rect spriteBox, SDL_Texture* texture, SDL_Rect clip_, Entity entity);
	void render(SDL_Renderer* renderer);
	void render(SDL_Renderer* renderer, Viewport viewport);
	void set(Entity entity, SDL_Texture* texture, SDL_Rect* clip);
	void set(int x, int y, Entity entity, SDL_Texture* texture, SDL_Rect* clip);
	SDL_Rect getBox();
	FileData getFileData();
private:
	SDL_Rect spriteBox_;
	SDL_Texture* texture_;
	SDL_Rect clip_;
	Entity type_;
};

#endif