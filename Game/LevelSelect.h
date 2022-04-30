#ifndef LEVEL_SELECT_H_INCLUDED
#define LEVEL_SELECT_H_INCLUDED

#include "GameState.h"
#include "LevelButton.h"
#include <vector>

class Game;
struct InputData;
class LevelButton;


class LevelSelect : public GameState {
public:

	LevelSelect(EntityFactory* entityFactory, AudioPlayer* audio);
	~LevelSelect();

	void enter();
	void exit();

	void handleInput(Game* game, InputData* input);
	void update(Game* game);
	void render(Game* game, Renderer* renderer);

	void pause() {};
	void resume() {};

	void nextButton();
	void previousButton();
	void changeButton();
private:

	std::vector<LevelButton*> stageButtons_;
	//std::vector<std::string> stageNames_;
	std::vector<LevelButton*> progressButtons_;

	void makeStageButtons(EntityFactory* entityFactory);
	void makeProgressButtons(EntityFactory* entityFactory);

	LevelButton* header_;

	EntityFactory* entityFactory_;

	int activeButtonIndex_;
	LevelButton* activeButton_;

	AudioPlayer* audio_;

	void executeButton();
};

#endif