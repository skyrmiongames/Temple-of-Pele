#pragma once

#include "Skyrmion/Node.h"
#include "Skyrmion/tiling/GridMaker.h"
#include "Skyrmion/tiling/LightMap.h"
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
		bool _invulnerable = false
	) : Node(_layer, _size, false, NULL), health(_health), max_health(_health), attack_power(_attack_power), invulnerable(_invulnerable)
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

	// virtual void update() {};

	static sf::Vector2f playerPos;
	static MapIndexer *mazeIndex;
	static MapIndexer *mazeFireballIndex;
	static LightMap *lighting;

protected:
	int health;
	int max_health;
	int attack_power;
	bool invulnerable;
	Textures textures;
};