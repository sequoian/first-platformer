#ifndef OPTIONS_H_INCLUDED
#define OPTIONS_H_INCLUDED

#include "GameState.h"
#include "OptionButton.h"
#include <vector>

class Game;
struct InputData;
class OptionButton;


class Options : public GameState {
public:

	Options(EntityFactory* entityFactory, AudioPlayer* audio);
	~Options();

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

	std::vector<OptionButton*> buttons_;
	std::vector<OptionButton*> soundVolumes_;
	std::vector<OptionButton*> musicVolumes_;

	// make it a button?
	OptionButton* header_;

	int activeButtonIndex_;
	OptionButton* activeButton_;
	OptionButton* activeSoundButton_;
	OptionButton* activeMusicButton_;

	AudioPlayer* audio_;
	int soundVolume_;
	int musicVolume_;


	void lowerVolume();
	void raiseVolume();

	void makeSoundVolumes(EntityFactory* entityFactory);
	void makeMusicVolumes(EntityFactory* entityFactory);
};

#endif