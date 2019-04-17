#pragma once

#include <string>
#include <list>
#include "Node.h"

/*
 * Created by Stuart Irwin on 4/13/2019.
 * Manages list of nodes through update cycle
 */

class UpdateList {
private:
	static std::list<Node*> onScreen;
	static std::list<Node*> offScreen;

	//Sort nodes on screen
	static bool checking_screen;
	static void update_lists();

	//Check if node has moving collisionlayer
	static bool moving_layer(Node *n);

public:
	//Manage node lists
	static void add_node(Node *next);
	static void remove_node(Node *extra);

	//Schedule screen list update on next cycle
	static void check_screen();

	//Update all nodes in list
	static void update(sf::RenderWindow &window);
};