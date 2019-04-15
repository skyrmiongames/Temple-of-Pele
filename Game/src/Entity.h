#pragma once

#include "Node.h"

class Entity : public Node {

public:
	Entity(
		int _health = 20,
		int _attack_power = 20,
		bool _invulnerable = false,
		double _speed = 1.0
	) : health(_health), attack_power(_attack_power), invulnerable(_invulnerable), speed(_speed), Node() {}
	~Entity() {}

	int modify_health(int modifier) {
		if (!invulnerable || modifier > 0) set_health(get_health() + modifier);

		if (is_dead()) {
			// Death code
		}

		return get_health();
	}

	void set_health(int _health) { health = _health <= max_health ? _health : max_health; }

	int get_health() { return health; }

	bool is_dead() { return health <= 0; }

	int get_attack() { return attack_power; }

	void move(OrthagonalDirection direction) {

	}

protected:
	int health;
	int max_health;
	int attack_power;
	bool invulnerable;
	double speed;
};
