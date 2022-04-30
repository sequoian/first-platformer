#include "AirBrush.h"

void AirBrush::input(InputData data) {
	cursor_->setPosition(data.mouseX, data.mouseY);
	if (data.mouseHeld) {
		cursor_->draw(entity_, texture_, &clip_);
	}
	if (data.brush == Entity::Entity_SolidTile) {
		cursor_->changeBrush(Entity::Entity_SolidTile);
	}
	else if (data.brush == Entity::Entity_Player) {
		cursor_->changeBrush(Entity::Entity_Player);
	}
	else if (data.brush == Entity::Entity_DamageTile) {
		cursor_->changeBrush(Entity::Entity_DamageTile);
	}
	else if (data.brush == Entity::Entity_StageGoal) {
		cursor_->changeBrush(Entity::Entity_StageGoal);
	}
}