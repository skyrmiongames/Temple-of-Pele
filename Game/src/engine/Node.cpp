#include "Node.h"

/*
 * Created by Stuart Irwin on 4/16/2019.
 * Sprite with collision
 */

//Base constructor
Node::Node(sf::Vector2i size) {
	setSize(size);
}

//Get node type variable
int Node::getType() {
	return type;
}

//Get collision box size
sf::Vector2i Node::getSize() {
	return size;
}

//Get next node in list
Node *Node::getNext() {
	return next;
}

//Check if node is hidden
bool Node::isHidden() {
	return hidden || deleted;
}

//Set node type variable
void Node::setType(int type) {
	this->type = type;
}

//Set collision box size
Node::setSize(sf::Vector2i size) {
	this->size = size;
	setOrigin(size.x / 2, size.y / 2);
}

//Set whether node is hidden
void Node::setHidden(bool hidden) {
	this->hidden = hidden;
}

//Get full collision bitset
bitset<MAXLAYER> Node::getCollisionLayer() {
	return collisionLayers;
}

//Check if node collides with layer
bool Node::getCollisionLayer(unsigned char layer) {
	if(layer >= MAXLAYER)
		throw new invalid_argument(LAYERERROR);
	return collisionLayers[layer];
}

//Set if node collides with layer
void Node::setCollisionLayer(unsigned char layer, bool collides) {
	if(layer >= MAXLAYER)
		throw new invalid_argument(LAYERERROR);
	collisionLayers[layer] = collides;
}

//Check collision box against other node
bool Node::checkCollision(Node *other) {
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