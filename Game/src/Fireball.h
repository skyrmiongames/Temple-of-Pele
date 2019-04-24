#pragma once

#include "Enemy.h"
#include "textures.h"
#include "Node.h" // for access to playerPos

class Fireball : public Enemy {
public:
	Fireball(
		sf::Vector2f _location,
		float _angle = 400, // using Conway's constant for an interesting value that will probably never occur
		float _speed = 0.1

	) : Enemy(FIREBALL, sf::Vector2i(10, 10)) {
		setPosition(_location);
		angle = _angle == 400 ? angleTo(_location, playerPos): _angle;
		speed = _speed;

		curFrame = 1;
		maxFrame = 4;
		lastTime = 0.0;
		setTexture(textures->Fireball);
		setRotation(-90);
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
			set_delete();
		animateFireball(time);
	}

	void collide(Node* object) {
		if (object->get_layer() == SWORD || object->get_layer() == PLAYER)
		{
			set_delete();
		} //allow the player to block fireballs
	};

private:
	float angle;
	float speed;
	int curFrame;
	int maxFrame;
	double lastTime;
};