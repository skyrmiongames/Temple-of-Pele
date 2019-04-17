#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "enums.h"

/*
 * Created by Stuart Irwin on 4/13/2019.
 * Sprite with collision
 */

class Node : public sf::Sprite {
private:
	//Node variables
	CollisionLayer layer;
	sf::Vector2i size;

public:
	//Node construction
	Node(CollisionLayer layer=ENEMY);
	Node(sf::Vector2i *size, CollisionLayer layer=ENEMY);

	//Collision and visual engine
	bool on_screen();
	sf::Vector2i get_size();
	CollisionLayer get_layer();
	bool check_collision(Node *other);

	//Entity implementation
	virtual void on_load();
	virtual void update();
	virtual void collide(Node *object);
	virtual ~Node();
};