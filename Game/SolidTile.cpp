#include "SolidTile.h"

SolidTile::SolidTile(int id, Position position, SDL_Texture* texture, SDL_Rect* clip) 
	: Entity(id, position, texture, clip) {
	features_.isPlayer = false;
	features_.canCollide = true;
	features_.isPlatform = true;
}

SolidTile::~SolidTile() {

}

void SolidTile::move(Direction direction) {
	// because pure virtual
}

void SolidTile::onCollide(Entity* entity) {
	block(entity);
}

void SolidTile::handleInput(InputData data) {

}

void SolidTile::update() {

}