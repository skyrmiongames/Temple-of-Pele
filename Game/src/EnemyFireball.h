#pragma once

#include "Skyrmion/UpdateList.h"
#include "Enemy.h"
#include "Fireball.h"

class FireEnemy : public Enemy // Aside from shooting fireballs this enemy acts identically to the basic enemy
{
public:
	FireEnemy() : Enemy() {
	};
	~FireEnemy() {};

	void update(double time) {
		if (getPosition().x < playerPos.x)
			setTexture(textures.FireEnemyRightGif);
		else
			setTexture(textures.FireEnemyLeftGif);

		animateEnemy(time);

		sf::Vector2f dir = playerPos - getGPosition();
		move(time, dir, 16, false);
		fireballTimer(time, dir);
	}

	// times fireball spawning
	void fireballTimer(double time, sf::Vector2f dir) {
		if((nextTime -= time) <= 0) {
			nextTime = 4;
			UpdateList::addNode(new Fireball(getGPosition(), dir));
		}
	};

private:
	double nextTime = 4;
};