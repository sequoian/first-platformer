#ifndef AIR_TILE_H
#define AIR_TILE_H

#include "Entity.h"

class AirTile : public Entity {
public:
	AirTile(int id, Position position, SDL_Texture* texture, SDL_Rect* clip = nullptr);
	~AirTile();
	void move(Direction direction);
	void onCollide(Entity* entity);
	void handleInput(InputData data);
	void update();
private:
};

#endif