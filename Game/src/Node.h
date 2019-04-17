#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "enums.h"
#include "UpdateList.h"
#include "LogicComponents.hpp"

/*
 * Created by Stuart Irwin on 4/13/2019.
 * Sprite with collision
 */

class Node : public sf::Sprite, public LogicReciever
{
private:
	//Node variables
	CollisionLayer layer;
	sf::Vector2i size;
	bool loaded = false;

public:
	Node(CollisionLayer layer = ENEMY);
	Node(sf::Vector2i *size, CollisionLayer layer = ENEMY);

	//Base getters
	sf::Vector2i get_size();
	CollisionLayer get_layer();
	virtual bool get_hidden();

	//Collision and visual engine
	bool on_screen();
	bool check_collision(Node *other);
	void activate();

	//Entity implementation
	virtual void on_load();
	virtual void on_activate();
	virtual void update();
	virtual void collide(Node *object);
	virtual ~Node();
};