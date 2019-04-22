#pragma once

#include "Entity.h"
#include "textures.h"

#include <iostream>

class Enemy : public Entity {
public:
	Enemy() : Entity() {
		setTexture(textures->Enemy1Gif);
		set_isHazard(true);
	}
	~Enemy() {}

	void update(double time) {
		float playerAngle = atan( // This enemy is 1, player is 2.
			(-playerPos.y + getPosition().y)/
			(playerPos.x - getPosition().x)
		) + (getPosition().x > playerPos.x ? PI : 0);
		
		std::cout << playerAngle << std::endl;
		move(playerAngle, 0.005);
	}

private:

};