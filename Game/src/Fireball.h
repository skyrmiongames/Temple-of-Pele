#pragma once

#include "Enemy.h"

class Fireball : public Enemy {
public:
	Fireball(
		sf::Vector2f _location,
		sf::Vector2f _direction,
		float _speed = 60

	) : Enemy(FIREBALL, sf::Vector2i(10, 10)) {
		setPosition(_location);
		speed = _speed;
		direction = _direction;

		curFrame = 1;
		maxFrame = 4;
		setTexture(textures.Fireball);
		setRotation(-90);

		collideWith(SWORD);
		collideWith(PLAYER);
		collideWith(SWITCH);
	}
	~Fireball() {}

	// times fireball animation
	void timeFireBall(double time) {
		if((nextTime -= time) <= 0) {
			curFrame++;
			nextTime = 0.2;
			if(curFrame == maxFrame)
				curFrame = 1;
		}
	};

	// animates fireball
	void animateFireball(double time) {
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
		//Entity::lighting->removeSource(getGPosition().x / 16, getGPosition().y / 16);
		if(!move(time, direction, speed, true))
			setDelete();
		if(!isDeleted()) {
			animateFireball(time);

			//Update lighting location
			unsigned int x = getGPosition().x / 16;
			unsigned int y = getGPosition().y / 16;
			Entity::lighting->addSource(x, y, 0.6);
			Entity::lighting->reload();
		}
	}

	void collide(Node* object) {
		setDelete();
	};

private:
	sf::Vector2f direction;
	float speed;
	int curFrame;
	int maxFrame;
	double nextTime = 0;
};