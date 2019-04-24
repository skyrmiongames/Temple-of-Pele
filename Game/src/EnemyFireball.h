#pragma once

#include "Enemy.h"
#include "Fireball.h"

class FireEnemy : public Enemy
{
public:
	FireEnemy() : Enemy()
	{
		setTexture(textures->FireEnemyLeftGif);
	};
	~FireEnemy() {};

	void update(double time)
	{
		fireballTimer(time);
	}

	void fireballTimer(double time)
	{
		if (time - fireballCoolDown >= 5)
		{
			fireballCoolDown = time;
			new Fireball(getPosition());
		}
	};

private:
	double fireballCoolDown;
};