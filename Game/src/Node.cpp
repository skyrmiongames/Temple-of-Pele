#include "Node.h"

/*
 * Created by Stuart Irwin on 4/16/2019.
 * Sprite with collision
 */

//Default constructor
Node::Node(CollisionLayer layer) {
	sf::Vector2i size(16, 16);
	this->size = size;
	this->layer = layer;
}

//Base constructor
Node::Node(sf::Vector2i *size, CollisionLayer layer) {
	this->size = *size;
	this->layer = layer;
}

//Check if near/on screen
bool Node::on_screen() {
	return true;
}

//Get collision size
sf::Vector2i Node::get_size() {
	return size;
}

//Get collision layer
CollisionLayer Node::get_layer() {
	return layer;
}

//Check collision box against other node
bool Node::check_collision(Node *other) {
	//Get self box
	sf::Vector2f thisPos = this->getPosition();
	sf::Vector2i thisSize = this->get_size() / 2;

	//Get other box
	sf::Vector2f otherPos = other->getPosition();
	sf::Vector2i otherSize = other->get_size() / 2;

	//Check all cordinates
	return thisPos.x - thisSize.x < otherPos.x + otherSize.x && 
		thisPos.x + thisSize.x > otherPos.x - otherSize.x &&
		thisPos.y - thisSize.y < otherPos.y + otherSize.y && 
		thisPos.y + thisSize.y > otherPos.y - otherSize.y;
}

//Define virtual placeholders
void Node::on_load() {}
void Node::update() {}
void Node::collide(Node *object) {}
Node::~Node() {}