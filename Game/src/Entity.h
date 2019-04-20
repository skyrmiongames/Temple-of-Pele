#pragma once

#include "Node.h"
#include "enums.h"
#include "Helpers.h"
#include "GridMaker.h"

#include <math.h>


class Entity : public Node {

public:
	Entity(
		int _health = 60,
		int _attack_power = 20,
		double _speed = 1.0,
		bool _invulnerable = false,
		CollisionLayer _layer = ENEMY,
		sf::Vector2i _size = sf::Vector2i(16, 16)
	) : Node(_layer, _size), health(_health), max_health(_health), attack_power(_attack_power), speed(_speed), invulnerable(_invulnerable) 
	{
		setOrigin(_size.x / 2, _size.y / 2);
	}

	~Entity() {}

	int modify_health(int modifier) {
		if (!invulnerable || modifier > 0) set_health(get_health() + modifier);

		if (is_dead()) {
			// TODO: implement death code
		}

		return get_health();
	}

	void set_health(int _health, bool updateMax = false) { 
		if (updateMax) max_health = _health;
		health = _health <= max_health ? _health : max_health; 
	}

	int get_health() { return health; }

	bool is_dead() { return health <= 0; }

	int get_attack() { return attack_power; }

	void move(
		OrthagonalDirection direction, 
		float distance = 0.1,
		bool allowVoid = false
	) {

		float angle
			= direction == North ? (3 * PI) / 2
			: direction == East ? PI
			: direction == West ? 0
			: direction == South ? PI / 2
			: direction == Northeast ? (3 * PI) / 4
			: direction == Northwest ? (PI) / 4
			: direction == Southwest ? (7 * PI) / 4
			: direction == Southeast ? (5 * PI) / 4
			: 0;

		move(angle, distance, allowVoid);
		
	}

	void move(
		float angle = 0.0,
		float distance = 0.1,
		bool allowVoid = true
	) {

		float xOffset = cos(angle) * distance;
		float yOffset = sin(angle) * distance;

		sf::Vector2f target(getPosition().x + xOffset, getPosition().y + yOffset);
		TileType targetType = GridMaker::check_tile(target);

		if (targetType != WALL && (!allowVoid ? targetType != EMPTY : true)) {
			setPosition(sf::Vector2f(target.x, target.y));
		}
	}

	virtual void update() {};

protected:
	int health;
	int max_health;
	int attack_power;
	double speed;
	bool invulnerable;
};