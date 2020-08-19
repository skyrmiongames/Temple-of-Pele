#include "Node.h"

/*
 * Created by Stuart Irwin on 4/16/2019.
 * Sprite with collision
 */

//Base constructor
Node::Node(unsigned char layer, sf::Vector2i size, bool hidden, Node *parent) {
	setSize(size);
	setHidden(hidden);
	setLayer(layer);
	setParent(parent);
}

//Get node layer variable
int Node::getLayer() {
	return layer;
}

//Get collision box size
sf::Vector2i Node::getSize() {
	return size;
}

//Get parent node
Node *Node::getParent() {
	return parent;
}

//Get global position
sf::Vector2f Node::getGPosition() {
	if(parent != NULL)
		return getPosition() + parent->getGPosition();
	return getPosition();
}

//Create position in a direction and distance
sf::Vector2f Node::getShiftedPosition(double time, sf::Vector2f dir, int distance) {
	float xOffset = 0;
	float yOffset = 0;
	if(dir.x == 0)
		yOffset = time * copysign(distance, dir.y);
	else if(dir.y == 0)
		xOffset = time * copysign(distance, dir.x);
	else if(abs(dir.x) == abs(dir.y)) {
		time *= sqrt(2) / 2.0;
		xOffset = time * copysign(distance, dir.x);
		yOffset = time * copysign(distance, dir.y);
	} else {
		float angle = std::atan2(dir.y, dir.x);
		xOffset = cos(angle) * distance * time;
		yOffset = sin(angle) * distance * time;
	}

	return sf::Vector2f(getPosition().x + xOffset, getPosition().y + yOffset);
}

//Check if node is hidden
bool Node::isHidden() {
	return hidden || deleted;
}

//Set node layer variable
void Node::setLayer(unsigned char layer) {
	if(layer >= MAXLAYER)
		throw new std::invalid_argument(LAYERERROR);
	this->layer = layer;
}

//Set collision box size
void Node::setSize(sf::Vector2i size) {
	this->size = size;
	setOrigin(size.x / 2, size.y / 2);
}

//Set whether node is hidden
void Node::setHidden(bool hidden) {
	this->hidden = hidden;
}

//Set parent node
void Node::setParent(Node *parent) {
	this->parent = parent;
}

//Get full collision bitset
std::bitset<MAXLAYER> Node::getCollisionLayers() {
	return collisionLayers;
}

//Check if node collides with layer
bool Node::getCollisionLayer(unsigned char layer) {
	if(layer >= MAXLAYER)
		throw new std::invalid_argument(LAYERERROR);
	return collisionLayers[layer];
}

//Set if node collides with layer
void Node::collideWith(unsigned char layer) {
	if(layer >= MAXLAYER)
		throw new std::invalid_argument(LAYERERROR);
	collisionLayers[layer] = true;
}

//Check collision box against other node
bool Node::checkCollision(Node *other) {
	if(other == NULL || other->isDeleted())
		return false;

	//Get self box
	sf::Vector2f thisPos = this->getGPosition();
	sf::Vector2i thisSize = this->getSize() / 2;

	//Get other box
	sf::Vector2f otherPos = other->getGPosition();
	sf::Vector2i otherSize = other->getSize() / 2;

	//Check all cordinates
	return thisPos.x - thisSize.x <= otherPos.x + otherSize.x &&
		thisPos.x + thisSize.x >= otherPos.x - otherSize.x &&
		thisPos.y - thisSize.y <= otherPos.y + otherSize.y &&
		thisPos.y + thisSize.y >= otherPos.y - otherSize.y;
}

//Get next node in list
Node *Node::getNext() {
	return next;
}

//Add new node after this
void Node::addNode(Node *node) {
	if(next == NULL)
		next = node;
	else
		next->addNode(node);
}

//Remove node immdiately after this from list
void Node::deleteNext() {
	if(next != NULL && next->isDeleted()) {
		next = next->getNext();
	}
}

//Check for deletion mark
bool Node::isDeleted() {
	return deleted;
}

//Mark for deletion
void Node::setDelete() {
	deleted = true;
}
Node::~Node() {}

//Define virtual placeholders
void Node::update(double time) {}
void Node::collide(Node *object) {}
void Node::collide(Node *object, double time) {
	collide(object);
}