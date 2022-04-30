#ifndef HELPERS_H
#define HELPERS_H

#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>

const int msPerSecond = 1000;
const int g_TimeStepFPS = 50;

typedef double Time;

// Stores which buttons/keys have been pressed
struct InputData {
	bool quit;
	bool pauseHeld;
	bool pauseHeldPreviously;
	bool leftHeld;
	bool leftHeldPreviously;
	bool rightHeld;
	bool rightHeldPreviously;
	bool upHeld;
	bool upHeldPreviously;
	bool downHeld;
	bool downHeldPreviously;
	bool jumpHeld;
	bool jumpHeldPreviously;
	bool runHeld;
	bool skipHeld;
	bool skipHeldPreviously;
	bool restartHeld;
	bool restartHeldPreviously;

	InputData() {};
	InputData(bool flag) {
		quit = flag;
		leftHeld = flag;
		rightHeld = flag;
		rightHeldPreviously = flag;
		leftHeldPreviously = flag;
		upHeld = flag;
		upHeldPreviously = flag;
		downHeld = flag;
		downHeldPreviously = flag;
		jumpHeld = flag;
		jumpHeldPreviously = flag;
		runHeld = flag;
		pauseHeld = flag;
		pauseHeldPreviously = flag;
		skipHeld = flag;
		skipHeldPreviously = flag;
		restartHeld = flag;
		restartHeldPreviously = flag;
	}
};

// Data needed by the renderer to render an object
struct RenderData {
	SDL_Texture* texture;
	SDL_Rect* source;
	SDL_Rect* destination;
	SDL_RendererFlip flip;
};

// A more precise (non-pixel) representation of x and y position
struct Position {
	float x;
	float y;
};

struct EntityFeatures {
	bool isPlayer;
	bool canCollide;
	bool isPlatform;
};

struct CollisionData {
	bool floor;
	bool roof;
	bool wall;
	bool wallLeft;
	bool wallRight;

	CollisionData() {
		reset();
	}
	void reset() {
		floor = false;
		roof = false;
		wall = false;
		wallLeft = false;
		wallRight = false;
	}
};

// Functor to be used as the deleter in smart pointers of SDL objects
struct SDL_Deleter {
	void operator() (SDL_Window* window) const {
		SDL_DestroyWindow(window);
		//std::cout << "Window destroyed." << std::endl;
	}
	void operator() (SDL_Renderer* renderer) const {
		SDL_DestroyRenderer(renderer);
		//std::cout << "Renderer destroyed." << std::endl;
	}
	void operator() (SDL_Texture* texture) const {
		SDL_DestroyTexture(texture);
		//std::cout << "Texture destroyed." << std::endl;
	}
	void operator() (Mix_Chunk* sound) const {
		Mix_FreeChunk(sound);
		//std::cout << "Sound destroyed." << std::endl;
	}
	void operator() (Mix_Music* music) const {
		Mix_FreeMusic(music);
		//std::cout << "Music track destroyed." << std::endl;
	}
};

struct Frame {
	Time timeInFrame;
	SDL_Rect clip;
};

enum TextureName {
	Texture_Hero,
	Texture_Stage,
	Texture_RedCube,
	Texture_CubeDeath,
	Texture_HeroSpawn,
	Texture_HeroVictory
};

enum class HeroAnimation {
	Standing,
	Walking,
	Running,
	Jumping,
	Falling,
	Clinging,
	Dead,
	Spawning,
	Victory
};

enum class Animations {
	Hero_Standing,
	Hero_Walking,
	Hero_Running,
	Hero_Jumping,
	Hero_Falling,
	Hero_Clinging,
	HeroDeath,
	Hero_Spawning,
	Hero_Victory
};

enum Direction {
	Direction_Up,
	Direction_Down,
	Direction_Left,
	Direction_Right,
	Direction_None
};

enum class SoundEffect {
	Jump,
	Death,
	Navigate,
	Forward,
	Back,
	Victory
};

enum class MusicTrack {
	Quickman,
	Flashman,
	VVVVVV,
};

#endif