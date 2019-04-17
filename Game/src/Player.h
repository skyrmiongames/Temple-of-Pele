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
//>>>>>>> 3e25be3c7d5cb874c4ca6eeef5714157990eac69
	~Player();

	void eightWayMovement();
	void update();

private:
	double x_velocity;
	double y_velocity;
	sf::Sprite healthSprite;
};
