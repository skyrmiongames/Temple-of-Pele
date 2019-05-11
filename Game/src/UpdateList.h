#pragma once

#include <string>
#include <vector>
#include <exception>
#include <iostream>
#include "Node.h"

/*
 * Created by Stuart Irwin on 4/13/2019.
 * Manages list of nodes through update cycle
 */

class UpdateList {
private:
	static std::vector<Node *> screen;
	static std::vector<Node *> added;
	static std::vector<Node *> deleted;
	static std::vector<Node *> rendering;
	static bool lock;

	//Check if node has moving collisionlayer
	static bool moving_layer(Node *n);

public:
	//Manage node lists
	static void add_node(Node *next);
	static void remove_nodes(std::vector<Node *> *list, std::vector<Node *> *deleting, bool permanent);

	//Update all nodes in list
	static void update(double time);
	static void draw(sf::RenderWindow &window);
};