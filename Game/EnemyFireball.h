#pragma once

#include "src\Enemy.h"
#include "src\Fireball.h"

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

	}

	void fireballTimer(double time)
	{
		if (time - fireballCoolDown >= 5)
		{
			fireballCoolDown = time;
			new Fireball fireball();
		}
	};

	void spawnFireBall(double time) 
	{
	
	};

private:
	double fireballCoolDown;
};