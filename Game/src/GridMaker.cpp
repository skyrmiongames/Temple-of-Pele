#include "GridMaker.h"

/*
 * Created by Stuart Irwin on 4/16/2019.
 * Generates and stores main tilemap
 */

//Static variables
char GridMaker::tiles[HEIGHT][WIDTH];
int GridMaker::indexes[HEIGHT * WIDTH];

//Convert file to char[][]
void GridMaker::build_grid() {
	//Get map file
	std::ifstream mapFile("resources/map.txt");

	//Set line variables
	int i = 0;
	std::string line;

	//Read file by line
	while(std::getline(mapFile, line)) {
		std::strcpy(tiles[i], line.c_str());
		i++;

		std::cout << tiles[i];
	}
}

//Convert char[][] to int[][]
int* GridMaker::index_grid() {
	//Loop through tiles
	for(int y = 0; y < HEIGHT; y++)
		for(int x = 0; x < WIDTH; x++)
			indexes[x + y * WIDTH] = index_tile(tiles[y][x]);

	return indexes;
}

//Get integer index of tile texture
int GridMaker::index_tile(char c) {
	switch(c) {
		case '#':
			return 3;
		case ' ': case '\0':
			return -1;
		default:
			return 0;
	}
}

//Get tile char from grid
char GridMaker::get_tile(sf::Vector2i position) {
	int x = position.x / 16;
	int y = position.y / 16;

	return tiles[y][x];
}

//Get tile phase from grid
TileType GridMaker::check_tile(sf::Vector2i position) {
	char c = get_tile(position);

	switch(c) {
		case '#':
			return WALL;
		case ' ': case '\0':
			return EMPTY;
		default:
			return GROUND;
	}
}