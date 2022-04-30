#include "DamageTile.h"

DamageTile::DamageTile(int id, Position position, SDL_Texture* texture, SDL_Rect* clip)
	: Entity(id, position, texture, clip) {
	features_.isPlayer = false;
	features_.canCollide = true;
	features_.isPlatform = false;

	setHitbox();
}

DamageTile::~DamageTile() {

}

void DamageTile::move(Direction direction) {
	// because pure virtual
}

void DamageTile::onCollide(Entity* entity) {
	block(entity);
	kill(entity);
}

void DamageTile::handleInput(InputData data) {

}

void DamageTile::update() {

}

void DamageTile::setHitbox() {
	hitBoxXoffset_ = 6;
	hitBoxYoffset_ = 6;

	hitBox_.x = renderBox_->x + hitBoxXoffset_;
	hitBox_.y = renderBox_->y + hitBoxYoffset_;
	hitBox_.w = renderBox_->w - 12;
	hitBox_.h = renderBox_->h - 12;

	hitBoxPos_.x = position_.x + hitBoxXoffset_;
	hitBoxPos_.y = position_.y + hitBoxYoffset_;
}