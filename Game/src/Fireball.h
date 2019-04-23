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

		setTexture(textures->healthSpriteTexture); // TODO: needs own texture file
	}
	~Fireball() {}

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