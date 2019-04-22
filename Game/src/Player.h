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
	void takeDamage(double time);

	void updateKey();
	void updateFrameTime(double time, int curFrame, int maxFrames);
	void updateTakeDamageTime(double time);
	void attack();

	bool getKey();

private:
	sf::Sprite healthSprite;
	Node knife;
	sf::View viewPlayer;
	bool hasKey;
	int curDirection;
	int curMoveFrame = 0;
	double lastAniTime;
	double lastDamageTime;
	bool endGame;
};
