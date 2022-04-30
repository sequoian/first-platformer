#ifndef STAGE_H
#define STAGE_H

#include <map>
#include <memory>
#include "GameState.h"
#include "Hero.h"
#include "Renderer.h"
#include "TextureCache.h"
#include "EntityFactory.h"
#include "Updater.h"
#include "Viewport.h"
#include <vector>


#include "Timer.h"

class Game;
struct InputData;

class Stage : public GameState {
public:

	Stage(EntityFactory* factory, AudioPlayer& audio, std::string stageFile, int stageNumber);
	~Stage();

	void enter();
	void exit();

	void handleInput(Game* game, InputData* input);
	void update(Game* game);
	void render(Game* game, Renderer* renderer);

	void pause();
	void resume();

	void addEntity(Entity* entity);

	SDL_Rect dimensions_;
	void victory();
	void launchNextStage();

private:
	//std::map<int, std::unique_ptr<Entity>> entities_;
	std::vector<std::unique_ptr<Entity>> entities_;
	Entity* player_;
	Updater updater_;
	AudioPlayer* audio_;
	Viewport viewport_;
	Timer timer_;
	EntityFactory* factory_;
	bool paused_;
	int stageNumber_;

	void readFile(const char* fileName);
	
	

};



#endif