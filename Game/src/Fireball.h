#pragma once

#include "Enemy.h"
#include "textures.h"

class Fireball : public Enemy {
public:
	Fireball(sf::Vector2f location, float _angle, float _speed = 0.5) : Enemy() {
		setPosition(location);
		setTexture(textures->healthSpriteTexture); // TODO: needs own texture file
	}
	~Fireball();

	void update(double time) {
		move(angle, speed, true);
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

};