#pragma once

#include "Node.h"
#include "enums.h"
#include "Helpers.h"

class Entity : public Node {

public:
	Entity(
		int _health = 60,
		int _attack_power = 20,
		double _speed = 1.0,
		bool _invulnerable = false
	) : health(_health), max_health(_health), attack_power(_attack_power), speed(_speed), invulnerable(_invulnerable) {}

	~Entity() {}

	int modify_health(int modifier) {
		if (!invulnerable || modifier > 0) set_health(get_health() + modifier);

		if (is_dead()) {
			// TODO: implement death code
		}

		return get_health();
	}

	void set_health(int _health) { health = _health <= max_health ? _health : max_health; }

	int get_health() { return health; }

	bool is_dead() { return health <= 0; }

	int get_attack() { return attack_power; }

	void move(OrthagonalDirection direction) {
		int xOffset
			= oneof(direction, 3, Northwest, North, Northeast) ? 1
			: oneof(direction, 3, Southwest, South, Southeast) ? -1
			: 0;

		int yOffset
			= oneof(direction, 3, Northeast, East, Southeast) ? 1
			: oneof(direction, 3, Northwest, West, Southwest) ? -1
			: 0;
	}

protected:
	int health;
	int max_health;
	int attack_power;
	double speed;
	bool invulnerable;
};
