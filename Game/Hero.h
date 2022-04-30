#ifndef HERO_H
#define HERO_H

#include "Entity.h"
#include "PlayerStateMachine.h"
#include "AudioPlayer.h"
#include "Animator.h"
#include "Effect.h"
#include "GameState.h"

class PlayerState;
class Animator;
class GameState;

class Hero : public Entity {
public:
	Hero(int id, Position position, SDL_Texture* texture, AudioPlayer* audio, Animator animator,
		Effect* deathEffect, Effect* spawnEffect, Effect* victoryEffect, GameState* gameState, 
		Timer* timer, SDL_Rect* clip = nullptr);
	~Hero();
	//void move(Direction direction);
	void onCollide(Entity* entity);
	void changeState(PlayerState* state);
	void handleInput(InputData data);
	void update();

	// abilities and state stuff
	void goLeft(bool runHeld);
	void goRight(bool runHeld);
	void slowToStop();

	void groundJump();
	void airJump();
	void wallJump(Direction direction);
	void jumpHigher();
	void stickToWall(Direction direction);

	CollisionData getCollisions() const;
	int getRunThreshold() const;
	int getAirJumpThreshold() const;
	int getAirJumps() const;
	void resetAirJumps();
	void respawn();
	void reset();
	void resetCollisions();
	void gravitate(int gravity);

	// animation tests
	RenderData getRenderData() ;
	void setAnimation(Animations animation);
	SDL_Rect clip_;
	void flip(Direction direction);

	void deathThroes();
	bool canRespawn();

	void restart();
	void victory();
	void endStage();

	Timer* timer_;
	

private:

	/*
	TODO
	At the moment, the animator MUST  be constructed before the state machine.  This is because
	the state machine makes a call to the animator when it is constructed.
	It creates the state, then calls it's enter() function, which call the change animation() function of animator.
	It's bad to have them so closely linked like this, so I'll need to find a way to fix this, probably by delaying the 
	call to the animator until after all the dust is settled.
	*/
	Animator animator_;
	const int walkMaxVelocity_ = 50;
	const int walkAcceleration_ = 15;
	const int runMaxVelocity_ = 150;
	const int runAcceleration_ = 20;
	const int groundDeceleration_ = 80;
	const int airDeceleration_ = 2;
	//const int deceleration_ = 50;
	PlayerStateMachine stateMachine_;
	const int maxAirJumps_ = 1;
	const int airJumpThreshold_ = -500;
	int currentAirJumps_;
	const float jumpHoldModifier_ = .40;
	const int groundJumpImpulse_ = 180;
	const int airJumpImpulse_ = 200;
	const int wallJumpVerticalImpulse_ = 185;
	const int wallJumpHorizontalImpulse_ = 150;
	const int gravity_ = 15;
	const int terminalVelocity_ = 350;

	AudioPlayer* audioPlayer_;
	Position spawnPoint_;
	Effect* deathEffect_;
	Effect* spawnEffect_;
	Effect* victoryEffect_;
	GameState* gameState_;
	

	Time timeDead_;


	void slowLeft(int targetVelocity);
	void slowRight(int targetVelocity);
};

#endif