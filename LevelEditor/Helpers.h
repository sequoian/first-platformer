#ifndef HELPERS_H
#define HELPERS_H

enum Entity {
	Entity_Player,
	Entity_SolidTile,
	Entity_AirTile,
	Entity_DamageTile,
	Entity_StageGoal
};

struct InputData {
	bool quit;
	bool saveHeld;
	bool saveHeldPreviously;
	Entity brush;
	bool mouseHeld;
	int mouseX;
	int mouseY;
	bool leftHeld;
	bool rightHeld;
	bool upHeld;
	bool downHeld;
};

struct FileData {
	int x;
	int y;
	Entity entity;
};

#endif