#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "GameState.h"
#include "MainButton.h"
#include <vector>

class Game;
struct InputData;
class MainButton;


class MainMenu : public GameState {
public:

	MainMenu(EntityFactory* entityFactory, AudioPlayer* audio);
	~MainMenu();

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

	std::vector<MainButton*> buttons_;
	//MainButton* play_;
	//MainButton* options_;
	//MainButton* exit_;

	// make it a button?
	MainButton* header_;

	int activeButtonIndex_;
	MainButton* activeButton_;
	AudioPlayer* audio_;
	EntityFactory* factory_;

	void executeButton(Game* game);
};

#endif