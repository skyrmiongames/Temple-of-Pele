#include "GridMaker.h"

/*
 * Created by Stuart Irwin on 4/16/2019.
 * Generates and stores main tilemap
 */

//Static variables
char GridMaker::tiles[HEIGHT][WIDTH];
int GridMaker::indexes[HEIGHT * WIDTH];

//Convert file to char[][]
void GridMaker::build_grid(std::string file) {
	//Get map file
	std::ifstream mapFile(file);

	//Set line variables
	int i = 0;
	std::string line;

	//Read file by line
	while(std::getline(mapFile, line)) {
		//Copy string
		for(int j = 0; line[j] != '\0'; j++)
			tiles[i][j] = line[j];

		i++;
	}
}

//Convert char[][] to int[][]
int* GridMaker::index_grid(bool animated) {
	//Loop through tiles
	for(int y = 0; y < HEIGHT; y++)
		for(int x = 0; x < WIDTH; x++) {
			//Get tile texture index
			indexes[x + y * WIDTH] = animated ? 
				animated_index_tile(tiles[y][x]) : index_tile(tiles[y][x]);
		}

	return indexes;
}

//Get integer index of tile texture
int GridMaker::index_tile(char c) {
	switch(c) {
		case '#': case '@':
			return 0;
		case',':
			return 4;
		case '*':
			return 2;
		case '+':
			return 3;
		case ' ': case '\0': case '~': case '=':
			return -1;
		default:
			return 1;
	}
}

//Get animated index of tile texture
int GridMaker::animated_index_tile(char c) {
	switch(c) {
		case '~': case '=':
			return 1;
		case '+':
			return 0;
		default:
			return -1;
	}
}

//Get tile char from grid
char GridMaker::get_tile(sf::Vector2f position) {
	int x = position.x / 16;
	int y = position.y / 16;

	return tiles[y][x];
}

//Get tile phase from grid
TileType GridMaker::check_tile(sf::Vector2f position) {
	char c = get_tile(position);

	switch(c) {
		case '#': case '+': case '@':
			return WALL;
		case ' ': case '\0': case '~': case '=':
			return EMPTY;
		default:
			return GROUND;
	}
}

//Set tile properties
void GridMaker::set_tile(sf::Vector2f position, char value) {
	int x = position.x / 16;
	int y = position.y / 16;

	tiles[y][x] = value;
}