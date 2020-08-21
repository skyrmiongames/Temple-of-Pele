#pragma once

#include "Skyrmion/Node.h"
#include "Skyrmion/GridMaker.h"
#include "enums.h"
#include "textures.h"

#include <math.h>

class Entity : public Node {

public:
	Entity(
		CollisionLayer _layer = ENEMY,
		sf::Vector2i _size = sf::Vector2i(10, 16),
		int _health = 60,
		int _attack_power = 20,
		double _speed = 1.0,
		bool _invulnerable = false
	) : Node(_layer, _size, false), health(_health), max_health(_health), attack_power(_attack_power), speed(_speed), invulnerable(_invulnerable)
	{
	}

	~Entity() {}

	int modify_health(int modifier) {
		if (!invulnerable || modifier > 0) set_health(get_health() + modifier);

		if (is_dead() && getLayer() != PLAYER) {
			setDelete();
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

	bool move(
		double time,
		sf::Vector2f dir,
		float distance = 56,
		bool allowVoid = false
	) {
		sf::Vector2f target = getShiftedPosition(time, dir, distance);
		int targetType = mazeIndex->getTile(target);

		if (targetType == AIR || (allowVoid && targetType == LAVA)) {
			setPosition(sf::Vector2f(target.x, target.y));
			return true;
		}
		return false;
	}

	// virtual void update() {};

	static sf::Vector2f playerPos;
	static Indexer *mazeIndex;

protected:
	int health;
	int max_health;
	int attack_power;
	double speed;
	bool invulnerable;
	Textures textures;
};