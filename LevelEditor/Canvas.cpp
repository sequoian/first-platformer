#include "Canvas.h"
#include <iostream>
#include <fstream>
#include "Globals.h"
//std::string g_fileName;


Canvas::Canvas(int width, int height, int cellWidth, int cellHeight, SDL_Texture* texture) {
	width_ = width;
	height_ = height;
	cellWidth_ = cellWidth;
	cellHeight_ = cellHeight;
	makeNewCells(texture);
}

Canvas::~Canvas() {
	delete player_;
	for (int i = 0; i < cells_.size(); ++i) {
		delete cells_[i];
	}
}

void Canvas::draw(int x, int y, Entity entity, SDL_Texture* texture, SDL_Rect* clip) {

	// hard coded size of cursor
	const int size = 5;
	SDL_Rect cursor = { x, y, size, size };

	std::vector<Cell*> touchedCells = findTouchedCells(&cursor);
	for (int i = 0; i < touchedCells.size(); ++i) {
		touchedCells[i]->set(entity, texture, clip);
	}
	
}

void Canvas::setSpawn(int x, int y, Entity entity, SDL_Texture* texture, SDL_Rect* clip) {
	player_->set(x, y, entity, texture, clip);
}

void Canvas::render(SDL_Renderer* renderer) {
	for (int i = 0; i < cells_.size(); ++i) {
		cells_[i]->render(renderer);
	}
	player_->render(renderer);
}

void Canvas::render(SDL_Renderer* renderer, Viewport viewport) {
	for (int i = 0; i < cells_.size(); ++i) {
		cells_[i]->render(renderer, viewport);
	}
	player_->render(renderer, viewport);
}

void Canvas::makeNewCells(SDL_Texture* texture) {

	// make player
	const SDL_Rect playerBox = { 0, 0, 20, 20 };
	const SDL_Rect playerClip = { 0, 0, 20, 20 };
	player_ = new Cell(playerBox, NULL, playerClip, Entity_Player);


	// figure out how many cells are on canvas
	const int numTilesWide = width_ / cellWidth_;
	const int numTilesHigh = height_ / cellHeight_;

	// set all cells as solid tiles
	const Entity entity = Entity::Entity_SolidTile;
	const SDL_Rect clip = { 20, 0, 20, 20 };

	// initialize positions to be altered in loop
	int xPos = 0;
	int yPos = 0;

	// fills out by column
	for (int xTiles = 0; xTiles < numTilesWide; ++xTiles, xPos += cellWidth_)
	{
		for (int yTiles = 0; yTiles < numTilesHigh; ++yTiles, yPos += cellHeight_)
		{
			SDL_Rect spriteBox = { xPos, yPos, cellWidth_, cellHeight_ };
			Cell* cell = new Cell(spriteBox, texture, clip, entity);
			cells_.push_back(cell);
		}
		yPos = 0;
	}
	xPos = 0;
}

std::vector<Cell*> Canvas::findTouchedCells(SDL_Rect* cursor) {
	std::vector<Cell*> touchedCells;
	for (int i = 0; i < cells_.size(); ++i) {
		if (checkCollision(*cursor, cells_[i]->getBox())) {
			touchedCells.push_back(cells_[i]);
		}
	}
	return touchedCells;
}

bool Canvas::checkCollision(SDL_Rect a, SDL_Rect b)
{
	int leftA, rightA, topA, bottomA;
	int leftB, rightB, topB, bottomB;

	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;

	// Returns false if A is outside B
	if (bottomA <= topB)
		return false;
	if (topA >= bottomB)
		return false;
	if (rightA <= leftB)
		return false;
	if (leftA >= rightB)
		return false;

	// Otherwise returns true
	return true;
}

// TODO
// Canvas does not need to know globals, simply take the filename.  
// Canvas loader will make sure the g_fileName has path and format.
// Be sure to change "backup" as well

void Canvas::write(std::string name) {
	std::ofstream file;

	//std::string name = g_fileName;
	name.insert(0, g_filePath);
	name.insert(name.size(), g_fileFormat);

	file.open(name.c_str());

	// write dimestions
	file << width_;
	file << ',';
	file << height_;
	file << '\n';

	// write tiles
	FileData data;
	for (int i = 0; i < cells_.size(); ++i) {
		data = cells_[i]->getFileData();
		file << data.x;
		file << ',';
		file << data.y;
		file << ",";
		file << data.entity;
		file << "\n";
	}
	// write player
	data = player_->getFileData();
	file << data.x;
	file << ',';
	file << data.y;
	file << ',';
	file << data.entity;

	file.close();
}

SDL_Rect Canvas::getRect() {
	SDL_Rect rect = { 0, 0, width_, height_ };
	return rect;
}