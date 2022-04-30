#include "StageGoal.h"

StageGoal::StageGoal(int id, Position position, SDL_Texture* texture, GameState* stage, SDL_Rect* clip)
	: Entity(id, position, texture, clip) {
	features_.isPlayer = false;
	features_.canCollide = true;
	features_.isPlatform = false;

	stage_ = stage;
}

StageGoal::~StageGoal() {

}

void StageGoal::move(Direction direction) {
	// because pure virtual
}

void StageGoal::onCollide(Entity* entity) {
	if (entity->getFeatures().isPlayer) {
		//stage_->done_ = true;
		entity->victory_ = true;
	}	
}

void StageGoal::handleInput(InputData data) {

}

void StageGoal::update() {

}