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
	static Node *(screen)[MAXLAYER];
	static std::vector<Node *> deleted;

public:
	//Manage node lists
	static void addNode(Node *next);

	//Update all nodes in list
	static void update(double time);
	static void draw(sf::RenderWindow &window);
};