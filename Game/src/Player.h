#pragma once

#include "Entity.h"
#include "textures.h"

class Player : public Entity , public textures
{
public:
	Player(
		double x_velocity = 0.0,
		double y_velocity = 0.0
	);
	~Player();

	void eightWayMovement();
	void update();

private:
	double x_velocity;
	double y_velocity;
	sf::Sprite healthSprite;
};
