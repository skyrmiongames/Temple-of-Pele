#include "GridMaker.h"

/*
 * Created by Stuart Irwin on 4/16/2019.
 * Generates and stores main tilemap
 */

//Convert file to char[][]
GridMaker::GridMaker(std::string file, unsigned int _width, unsigned int _height)
: height(_height), width(_width) {
	//Build array
	this->tiles = new char*[height];
	for(unsigned int i = 0; i < height; i++)
		tiles[i] = new char[width];
	reload(file);
}

void GridMaker::reload(std::string file) {
	//Set reading variables
	unsigned int i = 0;
	std::string line;
	std::ifstream mapFile(file);

	//Read file by line
	while(std::getline(mapFile, line) && i < height) {
		//Copy string
		unsigned int j = 0;
		while(line[j] != '\0' && line[j] != '\n' && j < width) {
			tiles[i][j] = line[j];
			++j;
		}

		//Blank out rest of line
		while(j < width)
			tiles[i][j++] = ' ';
		i++;
	}
	mapFile.close();

	//Blank out rest of grid
	while(i < height) {
		unsigned int j = 0;
		while(j < width)
			tiles[i][j++] = ' ';
		i++;
	}
}

GridMaker::~GridMaker() {

}

//Set tile value
void GridMaker::setTile(unsigned int x, unsigned int y, char value) {
	if(inBounds(x, y))
		tiles[y][x] = value;
}

//Get tile value
char GridMaker::getTile(unsigned int x, unsigned int y) {
	if(inBounds(x, y))
		return tiles[y][x];
	else return ' ';
}

//Get size of grid
sf::Vector2i GridMaker::getSize() const {
	return sf::Vector2i(width, height);
}

//Check cords vs grid size
bool GridMaker::inBounds(unsigned int x, unsigned int y) const {
	return x < width && y < height;
}

//Get value of tile
int Indexer::getTile(char c) {
	auto tile = indexes.find(c);
	if(tile != indexes.end())
		return tile->second;
	return fallback;
}

//Get tile char from grid
int Indexer::getTile(sf::Vector2f position) {
	unsigned int x = position.x / scale.x;
	unsigned int y = position.y / scale.y;
	if(grid->inBounds(x, y))
		return getTile(grid->getTile(x, y));
	return getTile(' ');
}

//Set tile in grid
void Indexer::setTile(sf::Vector2f position, int value) {
	unsigned int x = position.x / scale.x;
	unsigned int y = position.y / scale.y;
	if(grid->inBounds(x, y))
		grid->setTile(x, y, value);
}

//Convert char[][] to int[][]
int* Indexer::indexGrid() {
	const unsigned int width = grid->getSize().x;
	const unsigned int height = grid->getSize().y;
	int* indexes = new int[width * height];
	//Loop through tiles
	for(unsigned int y = 0; y < height; y++)
		for(unsigned int x = 0; x < width; x++) {
			//Get tile texture index
			indexes[x + y * width] = getTile(grid->getTile(x, y));
		}

	return indexes;
}

//Run function on every square in grid
void Indexer::mapGrid(std::function<void(char, sf::Vector2f)> func) {
	const unsigned int width = grid->getSize().x;
	const unsigned int height = grid->getSize().y;
	//Loop through tiles
	for(unsigned int y = 0; y < height; y++)
		for(unsigned int x = 0; x < width; x++) {
			sf::Vector2f pos = sf::Vector2f(x * scale.x, y * scale.y);
			func(grid->getTile(x, y), pos);
		}
}

//Get size of grid
sf::Vector2i Indexer::getSize() {
	return grid->getSize();
}