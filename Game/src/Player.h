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
	
	void attack(double time);
	bool attackCoolDown(double time);
	bool attackTime(double time);

	bool getKey();

private:
	sf::Sprite healthSprite;
	Node knifeV;
	Node knifeH;

	sf::View viewPlayer;
	
	bool hasKey;
	int curDirection;
	
	int curMoveFrame = 0;
	double lastAniTime;

	double lastDamageTime;
	
	bool endGame;

	double lastAttackTime;
	double attackAniTime;
};
