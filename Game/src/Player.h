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

private:
	sf::Sprite healthSprite;
	bool hasKey;
};
