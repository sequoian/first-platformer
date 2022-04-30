#ifndef DAMAGE_TILE_H_INCLUDED
#define DAMAGE_TILE_H_INCLUDED

#include "Entity.h"

class DamageTile : public Entity {
public:
	DamageTile(int id, Position position, SDL_Texture* texture, SDL_Rect* clip = nullptr);
	~DamageTile();
	void move(Direction direction);
	void onCollide(Entity* entity);
	void handleInput(InputData data);
	void update();
private:
	void setHitbox();
};

#endif