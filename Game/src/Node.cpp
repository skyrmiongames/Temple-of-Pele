#include "Node.h"

/*
 * Created by Stuart Irwin on 4/16/2019.
 * Sprite with collision
 */

//static variable reference thing
Textures *Node::textures;
sf::Vector2f Node::playerPos;

//Base constructor
Node::Node(CollisionLayer layer, sf::Vector2i size) {
	this->layer = layer;
	this->size = size;

	setOrigin(size.x / 2, size.y / 2);
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
UseAmount Node::is_singleton() {
	return MULTI;
}

//Get hidden value
bool Node::get_hidden() {
	return false;
}

//Check if near/on screen
bool Node::on_screen() {
	sf::Vector2f pos = getPosition();
	return pos.x > playerPos.x - 160 && 
		pos.x < playerPos.x + 160 &&
		pos.y > playerPos.y - 160 &&
		pos.y < playerPos.y + 160;
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
	return thisPos.x - thisSize.x <= otherPos.x + otherSize.x && 
		thisPos.x + thisSize.x >= otherPos.x - otherSize.x &&
		thisPos.y - thisSize.y <= otherPos.y + otherSize.y && 
		thisPos.y + thisSize.y >= otherPos.y - otherSize.y;
}


//Check for deletion mark
bool Node::get_delete() {
	return deleted;
}

//Mark for deletion
void Node::set_delete() {
	deleted = true;
}
Node::~Node() {}

//Define virtual placeholders
void Node::activate() {}
void Node::update(double time) {}
void Node::collide(Node *object) {}
void Node::collide(Node *object, double time) {
	collide(object);
}