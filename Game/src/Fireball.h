#pragma once

#include "Enemy.h"
#include "engine/Node.h" // for access to playerPos

class Fireball : public Enemy {
public:
	Fireball(
		sf::Vector2f _location,
		float _angle = 400, // using Conway's constant for an interesting value that will probably never occur
		float _speed = 2.5

	) : Enemy(FIREBALL, sf::Vector2i(10, 10)) {
		setPosition(_location);
		angle = _angle == 400 ? angleTo(_location, playerPos): _angle;
		speed = _speed;

		curFrame = 1;
		maxFrame = 4;
		lastTime = 0.0;
		setTexture(textures.Fireball);
		setRotation(-90);

		collideWith(SWORD);
		collideWith(PLAYER);
		collideWith(SWITCH);
	}
	~Fireball() {}

	// times fireball animation
	void timeFireBall(double time) {
		if (time - lastTime >= .2)
		{
			curFrame++;
			lastTime = time;
			if (curFrame == maxFrame)
			{
				curFrame = 1;
			}
		}
	};

	// animates fireball
	void animateFireball(double time)
	{
		timeFireBall(time);
		switch (curFrame)
		{
		case 1:
			setTextureRect(sf::IntRect(0, 0, 10, 8));
			break;
		case 2:
			setTextureRect(sf::IntRect(10, 0, 10, 8));
			break;
		case 3:
			setTextureRect(sf::IntRect(0, 8, 10, 8));
			break;
		case 4:
			setTextureRect(sf::IntRect(10, 8, 10, 8));
			break;
		}
	};

	void update(double time) {
		if(!move(angle, speed, true))
			setDelete();
		animateFireball(time);
	}

	void collide(Node* object) {
		setDelete();
	};

private:
	float angle;
	float speed;
	int curFrame;
	int maxFrame;
	double lastTime;
};