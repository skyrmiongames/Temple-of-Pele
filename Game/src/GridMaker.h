#pragma once

//SFML headers
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <fstream>
#include <string>
#include "enums.h"

/*
 * Created by Stuart Irwin on 4/15/2019.
 * Generates and stores main tilemap
 */

class GridMaker {
public:
	static const int WIDTH = 25;
	static const int HEIGHT= 15;

	//Build and convert grid
	static void build_grid(std::string file);
	static int* index_grid(bool animated=false);
	static int index_tile(char c);
	static int animated_index_tile(char c);
	
	//Retrieve tile properties
	static char get_tile(sf::Vector2f position);
	static TileType check_tile(sf::Vector2f position);

	//Set tile properties
	static void set_tile(sf::Vector2f position, char value);
private:
	static char tiles[HEIGHT][WIDTH];
	static int indexes[HEIGHT * WIDTH];
};