#ifndef SOLID_TILE_H
#define SOLID_TILE_H

#include "Entity.h"

class SolidTile : public Entity {
public:
	SolidTile(int id, Position position, SDL_Texture* texture, SDL_Rect* clip = nullptr);
	~SolidTile();
	void move(Direction direction);
	void onCollide(Entity* entity);
	void handleInput(InputData data);
	void update();
private:
};

#endif