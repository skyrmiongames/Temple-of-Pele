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
	static const int WIDTH = 21;
	static const int HEIGHT= 10;

	//Build and convert grid
	static void build_grid();
	static int* index_grid();
	static int index_tile(char c);
	
	//Retrieve tile properties
	static char get_tile(sf::Vector2i position);
	static TileType check_tile(sf::Vector2i position);

private:
	static char tiles[HEIGHT][WIDTH];
	static int indexes[HEIGHT * WIDTH];
};