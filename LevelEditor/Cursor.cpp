#include "Cursor.h"
#include <iostream>

Cursor::Cursor(Canvas* canvas, SDL_Texture* texture) {
	canvas_ = canvas;
	makeBrushes(texture);
	changeBrush(Entity_AirTile);
}

Cursor::~Cursor() {
	destroyBrushes();
}

void Cursor::input(InputData data) {
	currentBrush_->input(data);
}

void Cursor::input(InputData data, Viewport viewport) {
	SDL_Rect view = { data.mouseX, data.mouseY, 0, 0 };
	viewport.modifyMouse(view);
	data.mouseX = view.x;
	data.mouseY = view.y;
	currentBrush_->input(data);
}

void Cursor::draw(Entity entity, SDL_Texture* texture, SDL_Rect* clip) {
	if (entity != Entity_Player) {
		canvas_->draw(x_, y_, entity, texture, clip);
	}
	else {
		canvas_->setSpawn(x_, y_, entity, texture, clip);
	}
}

void Cursor::setPosition(int x, int y) {
	x_ = x;
	y_ = y;
}

void Cursor::changeBrush(Entity entity) {
	currentBrush_ = brushes_.at(entity);
}

void Cursor::makeBrushes(SDL_Texture* texture) {
	Entity entity;
	SDL_Rect clip;

	// Solid brush
	entity = Entity_SolidTile;
	clip = { 20, 0, 20, 20 };
	brushes_[entity] = new SolidBrush;
	brushes_[entity]->init(this, entity, texture, clip);

	// Player brush
	entity = Entity_Player;
	clip = { 40, 0, 20, 20 };
	brushes_[entity] = new PlayerBrush;
	brushes_[entity]->init(this, entity, texture, clip);

	// Air brush
	entity = Entity_AirTile;
	clip = { 0, 20, 20, 20 };
	brushes_[entity] = new AirBrush;	
	brushes_[entity]->init(this, entity, texture, clip);

	// Damage brush
	entity = Entity_DamageTile;
	clip = { 20, 20, 20, 20 };
	brushes_[entity] = new DamageBrush;
	brushes_[entity]->init(this, entity, texture, clip);

	// Goal brush
	entity = Entity_StageGoal;
	clip = { 0, 0, 20, 20 };
	brushes_[entity] = new GoalBrush;
	brushes_[entity]->init(this, entity, texture, clip);
}

void Cursor::destroyBrushes() {
	std::map<Entity, Brush*>::iterator itr;
	for (itr = brushes_.begin(); itr != brushes_.end(); ++itr) {
		delete itr->second;
	}
	brushes_.clear();
}