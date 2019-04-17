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

//Get collision size
sf::Vector2i Node::get_size() {
	return size;
}

//Get collision layer
CollisionLayer Node::get_layer() {
	return layer;
}

//Get logic single use limit
bool Node::is_singleton() {
	return false;
}

//Get hidden value
bool Node::get_hidden() {
	return false;
}

//Check if near/on screen
bool Node::on_screen() {
	return true;
}

//Check collision box against other node
bool Node::check_collision(Node *other) {
	//Get self box
	sf::Vector2f thisPos = this->getPosition();
	sf::Vector2i thisSize = this->get_size();

	//Get other box
	sf::Vector2f otherPos = other->getPosition();
	sf::Vector2i otherSize = other->get_size();

	//Check all cordinates
	return thisPos.x <= otherPos.x + otherSize.x && 
		thisPos.x + thisSize.x >= otherPos.x &&
		thisPos.y <= otherPos.y + otherSize.y && 
		thisPos.y + thisSize.y >= otherPos.y;
}

//Check for deletion mark
bool Node::get_delete() {
	return deleted;
}

//Mark for deletion
void Node::set_delete() {
	deleted = true;
}

//Destroy Node correctly
Node::~Node() {}

//Define virtual placeholders
void Node::on_load() {}
void Node::activate() {}
void Node::update() {}
void Node::collide(Node *object) {}