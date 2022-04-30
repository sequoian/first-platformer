#ifndef AUDIO_PLAYER_H_INCLUDED
#define AUDIO_PLAYER_H_INCLUDED

#include <SDL_mixer.h>
#include <string>
#include <map>
#include <memory>
#include "Helpers.h"
#include <assert.h>

class AudioPlayer {
public:
	AudioPlayer();
	void playSoundEffect(SoundEffect sound);
	void playMusicTrack(MusicTrack track);
	void pauseSound();
	void resumeSound();
	void pauseMusic();
	void resumeMusic();
	//void setSoundVolume(float modifier);
	//void setMusicVolume(float modifier);
	void setSoundVolume(int modifier);
	void setMusicVolume(int modifier);
	int getSoundVolume() const;
	int getMusicVolume() const;
private:
	std::map<SoundEffect, std::unique_ptr<Mix_Chunk, SDL_Deleter>> soundEffects_;
	std::map<MusicTrack, std::unique_ptr<Mix_Music, SDL_Deleter>> musicTracks_;
	int soundVolume_;
	int musicVolume_;

	Mix_Chunk* loadSound(std::string filePath);
	Mix_Music* loadMusic(std::string filePath);
};

#endif