//SFML headers
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

//Game headers
#include "NodeLoader.hpp"
#include "Player.h"
#include "engine/AnimatedTileMap.hpp"

#include <X11/Xlib.h>

sf::Vector2f Entity::playerPos;
Indexer *Entity::mazeIndex;

int main() {
	XInitThreads();

	//Load base tile map
	GridMaker grid("resources/maps/full_map.txt", 70, 33);
	TileMap map("resources/tiles/TileMap_Enviro.png", 16, 16, Indexer(&grid, displayIndex, 1));
	AnimatedTileMap aniMap("resources/tiles/TileMap_Gif.png", 16, 16, Indexer(&grid, animatedIndex, -1), 12);
	Entity::mazeIndex = new Indexer(&grid, collisionIndex, FLOOR, 16, 16);

    //Link tilemaps
    UpdateList::addNode(&map);
    UpdateList::addNode(&aniMap);

    //Set layers
    UpdateList::alwaysLoadLayer(MAP);
    UpdateList::alwaysLoadLayer(LOGIC);
    UpdateList::alwaysLoadLayer(GUI);
    UpdateList::alwaysLoadLayer(PLAYER);

    //Set up player
    Player player;
	player.setPosition(sf::Vector2f(456, 480));
	UpdateList::addNode(&player);

	//Set up selected room nodes
	Textures textures;
	spawn(textures);

	//Run game engine
	UpdateList::startEngine("Temple of Pele", sf::VideoMode(1200, 800));
	std::cout << "Done\n";
	return 0;
}