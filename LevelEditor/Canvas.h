#ifndef CANVAS_H
#define CANVAS_H

#include <vector>
#include <SDL.h>
#include "Cell.h"
#include "Helpers.h"
#include <string>
#include "Viewport.h"


class Canvas {
public:
	Canvas(int width, int height, int cellWidth, int cellHeight, SDL_Texture* texture);
	~Canvas();
	void draw(int x, int y, Entity entity, SDL_Texture* texture, SDL_Rect* clip);
	void setSpawn(int x, int y, Entity entity, SDL_Texture* texture, SDL_Rect* clip);
	void render(SDL_Renderer* renderer);
	void render(SDL_Renderer* renderer, Viewport viewport);
	void makeNewCells(SDL_Texture* texture);
	void write(std::string name);
	SDL_Rect getRect();
private:
	int width_;
	int height_;
	int cellWidth_;
	int cellHeight_;
	std::vector<Cell*> cells_;
	Cell* player_;

	std::vector<Cell*> findTouchedCells(SDL_Rect* cursor);
	bool checkCollision(SDL_Rect a, SDL_Rect b);

};

#endif