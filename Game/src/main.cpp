//SFML headers
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

//Game headers
#include "Skyrmion/AnimatedTileMap.hpp"
#include "Skyrmion/LightMap.hpp"
#include "NodeLoader.hpp"
#include "Player.h"

#include <X11/Xlib.h>

sf::Vector2f Entity::playerPos;
Indexer *Entity::mazeIndex;
LightMap *Entity::lighting;

int main() {
	XInitThreads();

	//Load base tile maps
	GridMaker grid("resources/maps/full_map.txt", 69, 33);
	TileMap map("resources/tiles/TileMap_Enviro.png", 16, 16, Indexer(&grid, displayIndex, 1));
	AnimatedTileMap aniMap("resources/tiles/TileMap_Gif.png", 16, 16, Indexer(&grid, animatedIndex, -1), 12, 0.3);
	Entity::mazeIndex = new Indexer(&grid, collisionIndex, AIR, 16, 16);

	//Create test Light map
	LightMap lighting(16, 16, 69, 33, LIGHTING);
	LightMap fireballLighting(16, 16, 69, 33, LIGHTING);
	Indexer mazeIndex = *Entity::mazeIndex;
	Entity::lighting = &fireballLighting;
	mazeIndex.mapGrid([&lighting, &fireballLighting, &mazeIndex](char c, sf::Vector2f pos) {
		unsigned int x = pos.x / 16;
		unsigned int y = pos.y / 16;
		if(c == '+')
			lighting.addSource(x, y, 1.0);
		else if(c == '>')
			lighting.addSource(x, y, 1.0);
		else {
			int type = mazeIndex.getTile(c);
			if(type == LAVA)
				lighting.addSource(x, y, 1.0);
			else if(type == SOLID) {
				lighting.addSolid(x, y);
				fireballLighting.addSolid(x, y);
			}
		}
	});
	lighting.reload();
	fireballLighting.reload();

    //Link tilemaps
    UpdateList::addNode(&map);
    UpdateList::addNode(&aniMap);
    UpdateList::addNode(&lighting);
    //UpdateList::addNode(&fireballLighting);

    //Set layers
    UpdateList::alwaysLoadLayer(MAP);
    UpdateList::alwaysLoadLayer(LOGIC);
    UpdateList::alwaysLoadLayer(GUI);
    UpdateList::alwaysLoadLayer(PLAYER);
    UpdateList::alwaysLoadLayer(LIGHTING);

    //Set up player
    Player player;
	player.setPosition(sf::Vector2f(456, 480));
	UpdateList::setCamera(&player, sf::Vector2f(300, 200));
	UpdateList::addNode(&player);

	//Game exit
	EndScreen winScreen(&lighting, true);
	winScreen.setPosition(69, 2);
	UpdateList::addNode(&winScreen);
	EndScreen loseScreen(&lighting, false);
	loseScreen.setParent(&player);
	UpdateList::addNode(&loseScreen);

	//Set up selected room nodes
	Textures textures;
	spawn(textures);

	//Run game engine
	UpdateList::startEngine("Temple of Pele", sf::VideoMode(1200, 800));
	std::cout << "Done\n";
	return 0;
}
