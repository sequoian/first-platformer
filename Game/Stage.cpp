#include "Helpers.h"
#include <iostream>
#include "Stage.h"
#include "Game.h"
#include "MainMenu.h"
#include "PauseScreen.h"

#include "AudioPlayer.h"
#include <fstream>

#include "Interpolator.h"

#include "PauseScreen.h"
#include "SaveGame.h"



/*
TODO
Hard coded stage dimensions.  Instead, get dimensions from file.  Make dimensions private
and allow others (like viewport) to get the data.
*/
Stage::Stage(EntityFactory* factory, AudioPlayer& audio, std::string stageFile, int stageNumber) 
	: audio_(&audio) 
{

	dimensions_.x = 0;
	dimensions_.y = 0;

	factory_ = factory;

	factory_->addTimer(&timer_);

	//factory->createEntities(this);
	readFile(stageFile.c_str());

	viewport_.setTarget(*player_);
	viewport_.setStage(dimensions_);

	timer_.start();
	paused_ = false;

	stageNumber_ = stageNumber;




	//audio_->setMusicVolume(0);
	//audio_->setSoundVolume(0);
}

Stage::~Stage() {
	//std::cout << "Stage destroyed..." << std::endl;
}

void Stage::enter() {
	//audio_->playMusicTrack(MusicTrack::Flashman);
	machine_->startStages();
	SaveGame::getInstance().setLastPlayed(stageNumber_);
	//std::cout << "Entered Stage" << std::endl;
}

void Stage::exit() {
	//std::cout << "Exited Stage" << std::endl;
}

void Stage::handleInput(Game* game, InputData* input) {

	//if (done_) {
	//	if (input->jumpHeld && !input->jumpHeldPreviously) {
	//		launchNextStage();
	//		return;
	//	}
	//}
	if (!paused_) {
		player_->handleInput(*input);
	}

	if (input->quit) {
		game->quit();
	}
	if (input->pauseHeld && !input->pauseHeldPreviously) {
		machine_->pushState(new PauseScreen(factory_, audio_, this));
	}
	//else if (input->restartHeld && !input->restartHeldPreviously) {
	//	player_->restart();
	//	done_ = false;
	//}
	else if (input->skipHeld && !input->skipHeldPreviously) {
		//launchNextStage();
		done_ = true;
		return;
	}


}

void Stage::update(Game* game) {
	
	if (paused_) {
		return;
	}

	if (!player_->isDead() && !player_->victory_) {
		updater_.update(player_);
	}


	for (auto itr = entities_.begin(); itr != entities_.end(); ++itr) {
		itr->get()->update();
	}


	//player_->update();
	viewport_.update();

	int i = 0;
	while (i < entities_.size()) {
		if (entities_[i].get()->isDone()) {
			entities_.erase(entities_.begin() + i);
		}
		else {
			++i;
		}
	}

	/*
	for (auto itr = entities_.begin(); itr != entities_.end();) {
		if (itr->get()->isDone()) {
			entities_.erase(itr);
		}
		else {
			++itr;
		}
	}
	*/

}


void Stage::render(Game* game, Renderer* renderer) {
	//renderer->clearScreen();



	for (auto itr = entities_.begin(); itr != entities_.end(); ++itr) {


		// This should happen in update, actually...
		RenderData data = itr->get()->getRenderData();
		if (viewport_.isInView(*data.destination)) {

			if (itr->get()->isDead() || itr->get()->victory_) {
				continue;
			}

			SDL_Rect renderBox = *data.destination;
			viewport_.modify(renderBox);
			
			// TODO implement interpolator
			//Interpolator::getInstance().interpolatePosition(renderBox, );

			data.destination = &renderBox;
			renderer->render(data);
		}


	}

	//renderer->render(player_->getRenderData());

	//renderer->presentScreen();

	if (done_) {
		//victory();
		launchNextStage();
	}

}
/*
void Stage::render(Game* game, Renderer* renderer) {
	renderer->clearScreen();

	for (std::map<int, std::unique_ptr<Entity>>::iterator itr = entities_.begin(); itr != entities_.end(); ++itr) {


		// This should happen in update, actually...
		RenderData data = itr->second->getRenderData();
		if (viewport_.isInView(*data.destination)) {
			SDL_Rect renderBox = *data.destination;
			viewport_.modify(renderBox);
			data.destination = &renderBox;
			renderer->render(data);
		}
		
		
	}

	//renderer->render(player_->getRenderData());

	renderer->presentScreen();
}
*/

void Stage::pause() {
	timer_.pause();
	paused_ = true;
	//audio_->pauseMusic();
	audio_->pauseSound();
	//std::cout << "PAUSED at " << timer_.getTime() << " ms" << std::endl;
}

void Stage::resume() {
	timer_.unpause();
	paused_ = false;
	//audio_->resumeMusic();
	audio_->resumeSound();
}


void Stage::addEntity(Entity* entity) {

	// put all entities in a general container that controls lifetime
	entities_.push_back(std::unique_ptr<Entity>(entity));

	// put entities in more specific containers
	EntityFeatures features = entity->getFeatures();
	if (features.isPlayer) {
		player_ = entity;
	}
	if (features.canCollide) {
		updater_.addCollidableObject(entity);
	}
}

/*
void Stage::addEntity(Entity* entity) {

	// put all entities in a general container that controls lifetime
	entities_.insert(
		std::pair<int, std::unique_ptr<Entity>>
		(entity->getID(), std::unique_ptr<Entity>(entity))
		);

	// put entities in more specific containers
	EntityFeatures features = entity->getFeatures();
	if (features.isPlayer) {
		player_ = entity;
	}
	if (features.canCollide) {
		updater_.addCollidableObject(entity);
	}
}
*/

void Stage::readFile(const char* fileName) {
	std::ifstream file;
	file.open(fileName);

	if (!file.is_open()) {
		//std::cout << "Stage file not found" << std::endl;
		assert(false);
	}


	char line[50];
	file.getline(line, 10, ',');
	int width = atoi(line);
	file.getline(line, 10, '\n');
	int height = atoi(line);
	dimensions_.w = width;
	dimensions_.h = height;

	while (!file.eof()) {
		file.getline(line, 10, ',');
		int x = atoi(line);
		//std::cout << line << std::endl;
		file.getline(line, 10, ',');
		int y = atoi(line);
		//std::cout << line << std::endl;
		file.getline(line, 30, '\n');
		int type = atoi(line);
		//std::cout << line << std::endl;
		//std::cout << x << ", " << y << ", " << type << std::endl;
		factory_->createEntity(x, y, type, this);
	}
	file.close();
}

void Stage::launchNextStage() {
	machine_->launchStage(++stageNumber_);
}

void Stage::victory() {
	audio_->playSoundEffect(SoundEffect::Victory);
	SaveGame::getInstance().setStageBeat(stageNumber_);
}