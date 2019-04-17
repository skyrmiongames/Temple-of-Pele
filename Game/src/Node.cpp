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

//get hidden value
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
	return thisPos.x =< otherPos.x + otherSize.x && 
		thisPos.x + thisSize.x > otherPos.x &&
		thisPos.y < otherPos.y + otherSize.y && 
		thisPos.y + thisSize.y > otherPos.y;
}

//Activate node from logic source
void activate() {
	if(!loaded) {
		//Add node to UpdateList
		UpdateList::add_node(this);
		on_load();
		loaded = true;
	} else
		on_activate();
}

//Destroy Node correctly
Node::~Node() {
	UpdateList::remove_node(this);
}

//Define virtual placeholders
void Node::on_load() {}
void Node::on_activate() {}
void Node::update() {}
void Node::collide(Node *object) {}