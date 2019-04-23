#pragma once

#include "Enemy.h"
#include "textures.h"
#include "Node.h" // for access to playerPos

class Fireball : public Enemy {
public:
	Fireball(
		sf::Vector2f location,
		float _angle = 1.30357, // using Conway's constant for an interesting value that will probably never occur
		float _speed = 0.5

	) : Enemy() {
		setPosition(location);
		angle = _angle == 1.30357 ? angleTo(location, playerPos): _angle;

		curFrame = 1;
		maxFrame = 4;
		lastTime = 0.0;
		setTexture(textures->Fireball); // TODO: needs own texture file
		setRotation(90);
	}
	~Fireball() {}

	void timeFireBall(double time) {
		if (time - lastTime >= .5)
		{
			curFrame++;
			lastTime = time; 
			if (curFrame == maxFrame)
			{
				curFrame = 1;
			}
		}
	};

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
		move(angle, speed, true);
		animateFireball(time);
	}

	void collide(Node* object) {
		Enemy::collide(object); //allow the player to block fireballs

		if (object->get_layer() == WALL) { // walls kill fireballs
			set_delete();
		}
	};

private:
	float angle;
	float speed;
	int curFrame;
	int maxFrame;
	double lastTime;
};