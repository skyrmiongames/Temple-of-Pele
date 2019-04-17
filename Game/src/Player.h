#pragma once

#include "Entity.h"
#include "textures.h"

class Player : public Entity
{
public:
	Player();

	~Player();

	void eightWayMovement();
	void update();

private:
	sf::Sprite healthSprite;
};
