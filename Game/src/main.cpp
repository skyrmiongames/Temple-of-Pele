//SFML headers
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <X11/Xlib.h>

//Game headers
#include "FullSpawner.hpp"
#include "engine/GridMaker.h"
#include "engine/AnimatedTileMap.hpp"

sf::Vector2f Entity::playerPos;

int main() {
	//Set texture loader
	Textures textures;

	XInitThreads();

	//Load base tile map
	GridMaker::build_grid("resources/maps/full_map.txt");
	TileMap map;
    if (!map.load("resources/tiles/TileMap_Enviro.png", sf::Vector2u(16, 16), GridMaker::index_grid(), GridMaker::WIDTH, GridMaker::HEIGHT))
        return -1;

    //Load animated tile map
	AnimatedTileMap aniMap;
    if (!aniMap.load("resources/tiles/TileMap_Gif.png", sf::Vector2u(16, 16), GridMaker::index_grid(true), GridMaker::WIDTH, GridMaker::HEIGHT, 12))
        return -1;

    //Link tilemaps
    UpdateList::addNode(&map);
    UpdateList::addNode(&aniMap);

    //Set layers
    UpdateList::nonCheckedLayer(MAP);
    UpdateList::nonCheckedLayer(LOGIC);
    UpdateList::nonCheckedLayer(GUI);
    UpdateList::nonCheckedLayer(PLAYER);

    //Set up player
    Player player;
	player.setPosition(sf::Vector2f(456, 480));
	UpdateList::addNode(&player);

	//Set up selected room nodes
	FullSpawner spawner;
	spawner.spawn(textures);

	//Run game engine
	startEngine("Temple of Pele", sf::VideoMode(1200, 800));
	std::cout << "Done\n";
	return 0;
}