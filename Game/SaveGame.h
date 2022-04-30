#pragma once

#include <vector>

class SaveGame {
public:
	~SaveGame();
	static SaveGame& getInstance();

	void readFile();
	void writeFile();
	void initNewFile();

	int checkStageAmount(int amount);
	void setStageBeat(int stageNum);
	bool getStageBeat(int stageNum) const;
	int getNumStages() const;
	int getNumStagesBeat() const;

	void setLastPlayed(int stageNum);
	int getLastPlayed() const;

	void setSoundVolume(int volume);
	int getSoundVolume() const;
	void setMusicVolume(int volume);
	int getMusicVolume() const;

private:
	SaveGame();
	const char* fileName_ = "Save.txt";
	std::vector<bool> stagesBeaten_;
	int lastStagePlayed_;
	int soundVolume_;
	int musicVolume_;

	// private copy ctor and assignment
	SaveGame(const SaveGame &);
	SaveGame& operator=(const SaveGame &);
};