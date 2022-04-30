#include "SaveGame.h"
#include <fstream>
#include <assert.h>
#include <iostream>

SaveGame::SaveGame() {

}

SaveGame::~SaveGame() {

}

SaveGame& SaveGame::getInstance() {
	static SaveGame instance;
	return instance;
}

void SaveGame::readFile() {
	std::ifstream file;
	file.open(fileName_);

	if (!file.is_open()) {
		initNewFile();
		return;
	}

	char line[50];
	file.getline(line, 10, ',');
	soundVolume_ = atoi(line);
	file.getline(line, 10, '\n');
	musicVolume_ = atoi(line);
	file.getline(line, 10, '\n');
	lastStagePlayed_ = atoi(line);
	file.getline(line, 10, '\n');
	stagesBeaten_.resize(atoi(line));
	

	for (int i = 0; i < stagesBeaten_.size(); ++i) {
		file.getline(line, 30, '\n');
		stagesBeaten_[i] = atoi(line);
	}

	file.close();
}

void SaveGame::writeFile() {
	std::ofstream file;
	file.open(fileName_);

	if (!file.is_open()) {
		assert(false);
	}

	file << soundVolume_;
	file << ',';
	file << musicVolume_;
	file << '\n';
	file << lastStagePlayed_;
	file << '\n';
	file << stagesBeaten_.size();
	file << '\n';

	for (int i = 0; i < stagesBeaten_.size(); ++i) {
		file << stagesBeaten_[i];
		file << "\n";
	}

	file.close();
}

void SaveGame::initNewFile() {
	//std::cout << "no save file found" << std::endl;
	soundVolume_ = 10;
	musicVolume_ = 10;
	lastStagePlayed_ = 0;
}

// checks and sets the stage amount
// should be called before anything dealing with stages occurs.  quick hack to avoid errors.
// returns 0 if matched, 1 if had to add stages, and 2 if had to remove stages
int SaveGame::checkStageAmount(int amount) {
	int amountMatched = 0;
	if (stagesBeaten_.size() < amount) {
		stagesBeaten_.resize(amount, false);
		amountMatched = 1;	
	}
	else if (stagesBeaten_.size() > amount) {
		stagesBeaten_.resize(amount);
		amountMatched = 2;
	}
	return amountMatched;
}

void SaveGame::setStageBeat(int stageNum) {
	if (stagesBeaten_.size() - 1 < stageNum) {
		assert(false);
	}
	stagesBeaten_[stageNum] = true;
}

bool SaveGame::getStageBeat(int stageNum) const {
	if (stagesBeaten_.size() - 1 < stageNum) {
		assert(false);
	}
	return stagesBeaten_[stageNum];
}

int SaveGame::getNumStages() const {
	return stagesBeaten_.size();
}

int SaveGame::getNumStagesBeat() const {
	int numberBeaten = 0;
	for (auto itr = stagesBeaten_.begin(); itr != stagesBeaten_.end(); ++itr) {
		if (*itr) {
			++numberBeaten;
		}
	}
	return numberBeaten;
}

void SaveGame::setLastPlayed(int stageNum) {
	if (stagesBeaten_.size() - 1 < stageNum) {
		assert(false);
	}
	lastStagePlayed_ = stageNum;
}

int SaveGame::getLastPlayed() const {
	return lastStagePlayed_;
}

void SaveGame::setSoundVolume(int volume) {
	soundVolume_ = volume;
}

int SaveGame::getSoundVolume() const {
	return soundVolume_;
}

void SaveGame::setMusicVolume(int volume) {
	musicVolume_ = volume;
}

int SaveGame::getMusicVolume() const {
	return musicVolume_;
}