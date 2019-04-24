#pragma once

#include "Entity.h"
#include "EndScreen.hpp"
#include "UpdateList.h"

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

	// vitual function definition, calls eightWayMovement, updateHealth, updateKey, and attack
	void update(double time);

	// virtual function definition, determines if player collides with enemy or key or endscreen
	void collide(Node *object, double time);

	// ends game when health is zero
	void die();

	// Draws additional sprites, healthSprite, keyIcon
	void drawGUI(sf::RenderWindow &window);
	// Draws game window around player
	void drawView(sf::RenderWindow &window);

	// Updates healthSprite and calls takeDamage
	void updateHealth(double time);
	// Activates invicibility frames on timer
	bool takeDamage(double time);
	// Timer for invicibility frames, called in takeDamage
	bool updateTakeDamageTime(double time);
	// setter for last damage time
	void setLastDamageTime(double newDamageTime);

	// moves sword sprite to player, used against enemies.
	void attack();

	// updates keyIcon's position based on hasKey
	void updateKey();

	// determines if player hasKey member is true or false
	bool getKey();
	// setter for if hasKey member
	void setKey(bool newHasKey);

private:
	// Player GUI
	sf::Sprite healthSprite;
	sf::Sprite keyIcon;

	// vertical and horizontal orientations of knife node for more precise hitboxes
	Node knifeV;
	Node knifeH;

	sf::View viewPlayer;
	
	bool hasKey;

	// determines which way the player is facing, 0 = down, 1 = up, 2 = right, 3 = left
	int curDirection;
	
	// current movment frame of player
	int curMoveFrame = 0;
	// time that the curMoveFrame member was changed
	double lastAniTime;

	// time the player was damaged
	double lastDamageTime;
	
	// turns true if player dies, called in die()
	bool endGame;
};
