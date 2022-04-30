#include "AirTile.h"

AirTile::AirTile(int id, Position position, SDL_Texture* texture, SDL_Rect* clip) 
	: Entity(id, position, texture, clip) {
	features_.isPlayer = false;
	features_.canCollide = false;
	features_.isPlatform = false;
}

AirTile::~AirTile() {

}

void AirTile::move(Direction direction) {
	// because pure virtual
}

void AirTile::onCollide(Entity* entity) {
	// because pure virtual
}

void AirTile::handleInput(InputData data) {

}

void AirTile::update() {

}