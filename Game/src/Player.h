#pragma once

#include "Skyrmion/UpdateList.h"
#include "Skyrmion/InputHandler.h"
#include "Entity.h"
#include "EndScreen.hpp"

/*
Player functions created by Benjamin Hoover
with exception of getKey(), collide() and die() made by Stuart Irwin
*/

class Player : public Entity
{
public:
	Player();

	~Player();

	// Movment related
	void eightWayMovement(double time);

	// Animates player based on timer and movment
	void animatePlayer(double time);
	// Timer for players movement animation, called in animate player
	void updateFrameTime(double time, int curFrame, int maxFrames);
	// Update lighting around player
	void updateLighting();

	// vitual function definition, calls eightWayMovement, updateHealth, updateKey, and attack
	void update(double time);

	// virtual function definition, determines if player collides with enemy or key or endscreen
	void collide(Node *object, double time);

	// ends game when health is zero
	void die();

	// Updates healthSprite and calls takeDamage
	void updateHealth(double time);
	// Activates invicibility frames on timer
	bool takeDamage(double time);

	// moves sword sprite to player, used against enemies.
	void attack();

	// determines if player hasKey member is true or false
	bool getKey();
	// setter for if hasKey member
	void setKey(bool newHasKey);

private:
	// Player GUI
	Node healthSprite;
	Node keyIcon;

	// vertical and horizontal orientations of knife node for more precise hitboxes
	Node knifeV;
	Node knifeH;

	bool hasKey = false;

	// determines which way the player is facing, 0 = down, 1 = up, 2 = right, 3 = left
	int curDirection;
	int curMoveFrame = 0;
	DirectionHandler input;

	int lightIndex;

	// timing
	double nextAniTime = 0;
	double nextDamageTime = 0;

	// turns true if player dies, called in die()
	bool endGame = false;
};
