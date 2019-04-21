#pragma once

#include "Entity.h"

class Enemy : public Entity {
public:
	Enemy() : Entity() {}
	~Enemy() {}

	void update() {
		float playerAngle = atan((playerPos.x - getPosition().x) / (playerPos.y - getPosition().y));
		move(playerAngle);
	}

private:

};