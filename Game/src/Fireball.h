#pragma once

#include "Enemy.h"
#include "textures.h"

class Fireball : public Enemy {
public:
	Fireball(sf::Vector2f location, float angle, float speed = 0.5) : Enemy() {
		setPosition(location);
		setTexture(textures->fireball);
	}
	~Fireball();

private:

};