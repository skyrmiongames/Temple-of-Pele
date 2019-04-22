#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "enums.h"
#include "LogicComponents.h"
#include "textures.h"

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
	bool deleted = false;

public:
	//Random static variables
	static Textures *textures;
	static sf::Vector2f playerPos;

	//Node constructors
	Node(CollisionLayer layer = ENEMY, sf::Vector2i size = sf::Vector2i(16, 16));

	//Base getters
	sf::Vector2i get_size();
	CollisionLayer get_layer();
	UseAmount is_singleton();
	virtual bool get_hidden();

	//Collision and visual engine
	bool on_screen();
	bool check_collision(Node *other);

	//Proper deletion procedure
	bool get_delete();
	void set_delete();
	virtual ~Node();

	//Entity implementation
	virtual void on_load();
	virtual void activate();
	virtual void update(double time);
	virtual void collide(Node *object);
	virtual void collide(Node *object, double time);
};