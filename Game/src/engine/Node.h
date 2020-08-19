#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <bitset>
#include <stdexcept>
#include <math.h>

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
	unsigned char layer;

	//Background system variables
	bool deleted = false;
	Node *next = NULL;

public:
	//Node constructors
	Node(unsigned char layer = 0,
		sf::Vector2i size = sf::Vector2i(16, 16),
		bool hidden = false,
		Node *parent = NULL);

	//General getters
	int getLayer();
	sf::Vector2i getSize();
	bool isHidden();
	Node *getParent();

	//Special getters
	sf::Vector2f getGPosition();
	sf::Vector2f getShiftedPosition(double time, sf::Vector2f dir, int distance);

	//General setters
	void setLayer(unsigned char layer);
	void setSize(sf::Vector2i size);
	void setHidden(bool hidden);
	void setParent(Node *parent);

	//Collision system
	std::bitset<MAXLAYER> getCollisionLayers();
	bool getCollisionLayer(unsigned char layer);
	void collideWith(unsigned char layer);
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