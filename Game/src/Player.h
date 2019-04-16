#pragma once

#include "Entity.h"

class Player : public Entity {
public:
	Player(
		double x_velocity = 0.0,
		double y_velocity = 0.0
	);
	~Player();

	void eightWayMovement();
	void slowDown();

private:
	double x_velocity;
	double y_velocity;
};
