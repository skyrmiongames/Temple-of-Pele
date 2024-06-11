#pragma once

#include "Entity.h"
#include "textures.h"
#include "Helpers.h"

class Enemy : public Entity {
public:
	Enemy(
		CollisionLayer _layer = ENEMY,
		sf::Vector2i _size = sf::Vector2i(10, 16)
	) : Entity(_layer, _size) {
		maxFrames = 6;
		curFrame = 1;
		collideWith(SWORD);
	}
	~Enemy() {}

	void update(double time) {
		if(getGPosition().x < playerPos.x)
			setTexture(textures.EnemyRightGif);
		else
			setTexture(textures.EnemyLeftGif);

		animateEnemy(time);
		move(playerPos - getGPosition(), mazeIndex, time*16);
	}

	void collide(Node *object) {
		setDelete();
	};

	void animateEnemy(double time) {
		animateTime(time);
		switch (curFrame)
		{
		case 1:
			setTextureRect(sf::IntRect(0, 0, 10, 16));
			break;
		case 2:
			setTextureRect(sf::IntRect(10, 0, 10, 16));
			break;
		case 3:
			setTextureRect(sf::IntRect(20, 0, 10, 16));
			break;
		case 4:
			setTextureRect(sf::IntRect(0, 16, 10, 16));
			break;
		case 5:
			setTextureRect(sf::IntRect(10, 16, 10, 16));
			break;
		case 6:
			setTextureRect(sf::IntRect(20, 16, 10, 16));
			break;
		}
	};

	void animateTime(double time) {
		if((nextTime -= time) <= 0) {
			nextTime = 0.1;
			curFrame++;
			if(curFrame == 6)
				curFrame = 1;
		}
	}

private:
	int maxFrames;
	int curFrame;
	double nextTime = 0;
};