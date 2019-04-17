#pragma once

#include "Entity.h"
#include "textures.h"

class Player : public Entity
{
public:
	Player();

	~Player();

	void eightWayMovement(double time);
	void update(double time);

private:
	sf::Sprite healthSprite;
};
