#pragma once

#include "Enemy.h"
#include "Fireball.h"

class FireEnemy : Enemy
{
public:
	FireEnemy() : Enemy()
	{
		setTexture(textures->FireEnemyLeftGif);
	};
	~FireEnemy() {};

	void update(double time)
	{
		spawnFireBall(time);
	}

	void fireballTimer(double time)
	{
		if (time - fireballCoolDown >= 5)
		{
			fireballCoolDown = time;
			new Fireball();
		}
	};

	void spawnFireBall(double time) 
	{
		if (abs(this->getPosition().x - playerPos.x) < 50 || 
			abs(this->getPosition().y - playerPos.y) < 50)
		{
			fireballTimer(time);
		}
	};

private:
	double fireballCoolDown;
};