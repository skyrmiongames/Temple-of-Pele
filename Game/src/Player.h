#pragma once

#include "Entity.h"
#include "EndScreen.hpp"
#include "UpdateList.h"

class Player : public Entity
{
public:
	Player();

	~Player();

	void eightWayMovement(double time);
	void animatePlayer(double time);
	void update(double time);
	void collide(Node *object, double time);
	void die();

	void drawGUI(sf::RenderWindow &window);
	void drawView(sf::RenderWindow &window);

	void updateHealth(double time);
	bool takeDamage(double time);
	void setLastDamageTime(double newDamageTime);

	void updateFrameTime(double time, int curFrame, int maxFrames);
	bool updateTakeDamageTime(double time);
	
	void attack();

	void updateKey();
	bool getKey();
	void setKey(bool newHasKey);

private:
	sf::Sprite healthSprite;
	sf::Sprite keyIcon;
	Node knifeV;
	Node knifeH;

	sf::View viewPlayer;
	
	bool hasKey;
	int curDirection;
	
	int curMoveFrame = 0;
	double lastAniTime;

	double lastDamageTime;
	
	bool endGame;
};
