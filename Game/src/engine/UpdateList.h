#pragma once

#include <string>
#include <vector>
#include <exception>
#include <bitset>
#include <thread>

#include <iostream>

#include "Node.h"

/*
 * Created by Stuart Irwin on 4/13/2019.
 * Manages list of nodes through update cycle
 */

class UpdateList {
private:
	static Node *(screen)[MAXLAYER];
	static std::bitset<MAXLAYER> nonCheckedLayers;
	static std::vector<Node *> deleted;
	static Node *camera;
	static sf::View viewPlayer;

public:
	//Manage node lists
	static void addNode(Node *next);
	static void setCamera(Node *follow, sf::Vector2f size);
	static void nonCheckedLayer(unsigned char layer);

	//Update loops
	static void update(double time);
	static void draw(sf::RenderWindow &window);
};

//Start engine
void startEngine(std::string title, sf::VideoMode mode);