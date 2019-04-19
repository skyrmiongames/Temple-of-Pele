#pragma once

#include "Entity.h"

class Player : public Entity
{
public:
	Player();

	~Player();

	void eightWayMovement(double time);
	void update(double time);
	void drawGUI(sf::RenderWindow &window);
	void updateHealth();
	void updateKey();
	void attack();

	bool getKey();

private:
	sf::Sprite healthSprite;
	Node *knife;
	bool hasKey;
	int curDirection;
};
