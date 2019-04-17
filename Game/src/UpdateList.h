#pragma once

#include <string>
#include <vector>
#include "Node.h"

/*
 * Created by Stuart Irwin on 4/13/2019.
 * Manages list of nodes through update cycle
 */

class UpdateList {
private:
	static std::vector<Node *> onScreen;
	static std::vector<Node *> offScreen;

	//Sort nodes on screen
	static bool checking_screen;
	static void update_lists();

	//Check if node has moving collisionlayer
	static bool moving_layer(Node *n);

public:
	//Manage node lists
	static void add_node(Node *next);
	static void remove_nodes();

	//Schedule screen list update on next cycle
	static void check_screen();

	//Update all nodes in list
	static void update(sf::RenderWindow &window);
};