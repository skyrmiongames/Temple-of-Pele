#pragma once

#include "Node.h"
#include "enums.h"
#include "Helpers.h"
#include "GridMaker.h"

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

	void move(
		int direction, 
		int distance = 1,
		bool allowVoid = true
	) {

		int xOffset // Assuming that right, 'east', is positive X
			= oneof(direction, 3, (int)Northeast, (int)East, (int)Southeast) ? distance
			: oneof(direction, 3, (int)Northwest, (int)West, (int)Southwest) ? -distance
			: 0;

		int yOffset // Assuming that up, 'north', is negative Y
			= oneof(direction, 3, (int)Northwest, (int)North, (int)Northeast) ? -distance
			: oneof(direction, 3, (int)Southwest, (int)South, (int)Southeast) ? distance
			: 0;

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
