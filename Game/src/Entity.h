#pragma once

#include "Node.h"

class Entity : public Node {

public:
	Entity(
		int _health = 20,
		int _attack_power = 5,
		bool _invulnerable = false,
		double _speed = 1.0
	) : health(_health), attack_power(_attack_power), invulnerable(_invulnerable), speed(_speed), Node() {}
	~Entity() {}

	void modify_health(int modifier) {
		if (!invulnerable) health += modifier;

		if (health <= 0) {
			// Death code
		}
	}

	int get_attack() { return attack_power; }

private:
	int health;
	int attack_power;
	bool invulnerable;
	double speed;
};
