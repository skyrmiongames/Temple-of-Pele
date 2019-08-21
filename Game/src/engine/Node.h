#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <bitset>
#include <stdexcept>
#include "LogicComponents.h"

#define MAXLAYER 16
#define LAYERERROR "Used collision layer > 16"

/*
 * Created by Stuart Irwin on 4/13/2019.
 * Sprite with collision
 */

class Node : public sf::Sprite {
private:
	//Visible system variables
	sf::Vector2i size;
	bool hidden = false;
	Node *parent = NULL;
	std::bitset<MAXLAYER> collisionLayers;

	//Background system variables
	bool deleted = false;
	Node *next = NULL;

	//Extra variable for general use
	int type;

public:
	//Node constructors
	Node(int type = 0, bool hidden = false, sf::Vector2i size = sf::Vector2i(16, 16));

	//General getters
	int getType();
	sf::Vector2i getSize();
	bool isHidden();
	Node *getParent();

	//General setters
	void setType(int type);
	void setSize(sf::Vector2i size);
	void setHidden(bool hidden);
	void setParent(Node *parent);

	//Collision system
	bitset<MAXLAYER> getCollisionLayer();
	bool getCollisionLayer(unsigned char layer);
	void setCollisionLayer(unsigned char layer, bool collides);
	bool checkCollision(Node *other);

	//Linked list functions
	Node *getNext();
	void addNode(Node *node);
	void deleteNext();

	//Proper deletion procedure
	bool isDeleted();
	void setDelete();
	virtual ~Node();

	//Entity implementation
	virtual void update(double time);
	virtual void collide(Node *object);
	virtual void collide(Node *object, double time);
};