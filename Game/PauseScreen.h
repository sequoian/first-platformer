#ifndef PAUSE_SCREEN_H
#define PAUSE_SCREEN_H


#include "GameState.h"
#include "PauseButton.h"
#include "Helpers.h"


class Game;
class PauseButton;

class PauseScreen : public GameState {
public:
	PauseScreen(EntityFactory* entityFactory, AudioPlayer* audio, GameState* pausedState);
	~PauseScreen();
	void enter();
	void exit();

	void handleInput(Game* game, InputData* input);
	void update(Game* game);
	void render(Game* game, Renderer* renderer);

	void pause() {};
	void resume() {};
private:
	PauseButton* header_;
	std::vector<PauseButton*> buttons_;
	GameState* pausedState_;
	AudioPlayer* audio_;
	EntityFactory* factory_;

	int activeButtonIndex_;
	PauseButton* activeButton_;

	void nextButton();
	void previousButton();
	void changeButton();
	void executeButton(Game* game);
};

#endif