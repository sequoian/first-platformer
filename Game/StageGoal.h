#ifndef STAGE_GOAL_H
#define STAGE_GOAL_H

#include "GameState.h"
#include "Entity.h"

class StageGoal : public Entity {
public:
	StageGoal(int id, Position position, SDL_Texture* texture, GameState* stage, SDL_Rect* clip = nullptr);
	~StageGoal();
	void move(Direction direction);
	void onCollide(Entity* entity);
	void handleInput(InputData data);
	void update();
private:
	GameState* stage_;
};

#endif