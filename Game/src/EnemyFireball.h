#pragma once

#include "Enemy.h"
#include "Fireball.h"
#include "engine/UpdateList.h"

class FireEnemy : public Enemy // Aside from shooting fireballs this enemy acts identically to the basic enemy
{
public:
	FireEnemy() : Enemy()
	{
	};
	~FireEnemy() {};

	void update(double time)
	{
		float playerAngle = angleTo(getPosition(), playerPos);

		if (getPosition().x < playerPos.x)
		{
			setTexture(textures.FireEnemyRightGif);
		}
		else
		{
			setTexture(textures.FireEnemyLeftGif);
		}

		animateEnemy(time);
		move(playerAngle, 0.005, false);
		fireballTimer(time);
	}

	// times fireball spawning
	void fireballTimer(double time)
	{
		if (nextTime > 0 && time >= nextTime)
		{
			nextTime = time + 5;
			UpdateList::addNode(new Fireball(getPosition(), 400, .07));
		}

		if (nextTime == -1)
		{
			nextTime = time + 5;
		}
	};

private:
	int nextTime = -1;
};