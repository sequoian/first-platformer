#include "AudioPlayer.h"
#include "SaveGame.h"

AudioPlayer::AudioPlayer() {

	// load sounds
	Mix_Chunk* loadedChunk = loadSound("Audio/jump.wav");
	soundEffects_[SoundEffect::Jump] = std::unique_ptr<Mix_Chunk, SDL_Deleter>(loadedChunk, SDL_Deleter());
	loadedChunk = loadSound("Audio/death2.wav");
	soundEffects_[SoundEffect::Death] = std::unique_ptr<Mix_Chunk, SDL_Deleter>(loadedChunk, SDL_Deleter());
	loadedChunk = loadSound("Audio/nav.wav");
	soundEffects_[SoundEffect::Navigate] = std::unique_ptr<Mix_Chunk, SDL_Deleter>(loadedChunk, SDL_Deleter());
	loadedChunk = loadSound("Audio/forward.wav");
	soundEffects_[SoundEffect::Forward] = std::unique_ptr<Mix_Chunk, SDL_Deleter>(loadedChunk, SDL_Deleter());
	loadedChunk = loadSound("Audio/back.wav");
	soundEffects_[SoundEffect::Back] = std::unique_ptr<Mix_Chunk, SDL_Deleter>(loadedChunk, SDL_Deleter());
	loadedChunk = loadSound("Audio/coin.wav");
	soundEffects_[SoundEffect::Victory] = std::unique_ptr<Mix_Chunk, SDL_Deleter>(loadedChunk, SDL_Deleter());

	// load music
	Mix_Music* loadedMusic = loadMusic("Audio/quickman.ogg");
	musicTracks_[MusicTrack::Quickman] = std::unique_ptr<Mix_Music, SDL_Deleter>(loadedMusic, SDL_Deleter());
	loadedMusic = loadMusic("Audio/flashman.ogg");
	musicTracks_[MusicTrack::Flashman] = std::unique_ptr<Mix_Music, SDL_Deleter>(loadedMusic, SDL_Deleter());
	loadedMusic = loadMusic("Audio/vvvvvv2.ogg");
	musicTracks_[MusicTrack::VVVVVV] = std::unique_ptr<Mix_Music, SDL_Deleter>(loadedMusic, SDL_Deleter());

	Mix_VolumeMusic(MIX_MAX_VOLUME * 0.8);
	Mix_Volume(-1, MIX_MAX_VOLUME);

	soundVolume_ = SaveGame::getInstance().getSoundVolume();
	setSoundVolume(soundVolume_);
	musicVolume_ = SaveGame::getInstance().getMusicVolume();
	setMusicVolume(musicVolume_);
}

void AudioPlayer::playSoundEffect(SoundEffect sound) {
	Mix_PlayChannel(-1, soundEffects_[sound].get(), 0);
}

void AudioPlayer::playMusicTrack(MusicTrack track) {
	Mix_PlayMusic(musicTracks_[track].get(), -1);
}

Mix_Chunk* AudioPlayer::loadSound(std::string filePath) {
	Mix_Chunk* chunk = Mix_LoadWAV(filePath.c_str());
	if (chunk != NULL) {
		return chunk;
	}
	else {
		assert(false);
	}
}

Mix_Music* AudioPlayer::loadMusic(std::string filePath) {
	Mix_Music* music = Mix_LoadMUS(filePath.c_str());
	if (music != NULL) {
		return music;
	}
	else {
		assert(false);
	}
}

/*
void AudioPlayer::setSoundVolume(float modifier) {
	assert(modifier >= 0 || modifier <= 1);
	int volume = int( MIX_MAX_VOLUME * modifier );
	Mix_Volume(-1, volume);
}

void AudioPlayer::setMusicVolume(float modifier) {
	assert(modifier >= 0 || modifier <= 1);
	int volume = int(MIX_MAX_VOLUME * modifier);
	Mix_VolumeMusic(volume);
}
*/

void AudioPlayer::setSoundVolume(int modifier) {
	assert(modifier >= 0 || modifier <= 10);
	soundVolume_ = modifier;
	int volume = int(MIX_MAX_VOLUME * (modifier * 0.1));
	Mix_Volume(-1, volume);
}

void AudioPlayer::setMusicVolume(int modifier) {
	assert(modifier >= 0 || modifier <= 10);
	musicVolume_ = modifier;
	int volume = int(MIX_MAX_VOLUME * (modifier * 0.1));
	Mix_VolumeMusic(volume);
}

void AudioPlayer::pauseSound() {
	Mix_Pause(-1);
}

void AudioPlayer::resumeSound() {
	Mix_Resume(-1);
}

void AudioPlayer::pauseMusic() {
	Mix_PauseMusic();
}

void AudioPlayer::resumeMusic() {
	Mix_ResumeMusic();
}

int AudioPlayer::getSoundVolume() const {
	return soundVolume_;
}

int AudioPlayer::getMusicVolume() const {
	return musicVolume_;
}