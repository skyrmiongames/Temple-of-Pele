//SFML headers
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

//Game headers
#include "Skyrmion/AnimatedTileMap.hpp"
#include "Skyrmion/LightMap.h"
#include "NodeLoader.hpp"
#include "Player.h"

sf::Vector2f Entity::playerPos;
Indexer *Entity::mazeIndex;
LightMap *Entity::lighting;

int main() {
	//Load settings file
	Settings::loadSettings("resources/settings.json");
	Textures textures;

	//Load base tile maps
	GridMaker grid("resources/maps/full_map.txt");
	TileMap map(&textures.environment, 16, 16, new Indexer(&grid, displayIndex, 1), MAP);
	AnimatedTileMap aniMap(&textures.animated, 16, 16, new Indexer(&grid, animatedIndex, -1), 12, 0.3, MAP);
	Entity::mazeIndex = new Indexer(&grid, collisionIndex, 1, 16, 16);

	//Create test Light map
	Indexer lightMap(&grid, lightIndex, 0, 2, 2);
	LightMap staticLighting(8, 8, 0.2, 0.05, lightMap, LIGHTING, true);
	LightMap fireballLighting(8, 8, 0, 0.05, lightMap, LIGHTING, false);
	Entity::lighting = &fireballLighting;
	LightMapCollection lighting(8, 8, lightMap, LIGHTING);
	lighting.addLightMap(&staticLighting);
	lighting.addLightMap(&fireballLighting);
	UpdateList::addNode(&lighting);

    //Link tilemaps
    UpdateList::addNode(&map);
    UpdateList::addNode(&aniMap);

    //Set layers
    UpdateList::staticLayer(MAP);
    UpdateList::staticLayer(LOGIC);
    UpdateList::staticLayer(GUI);
    UpdateList::staticLayer(FIREBALL);
    UpdateList::staticLayer(PLAYER);
    UpdateList::staticLayer(LIGHTING);

    //Set up player
    Player player;
	player.setPosition(sf::Vector2f(456, 480));
	UpdateList::setCamera(&player, sf::Vector2f(300, 200));
	UpdateList::addNode(&player);

	//Game exit
	EndScreen winScreen(true);
	winScreen.setPosition(69, 2);
	UpdateList::addNode(&winScreen);
	EndScreen loseScreen(false);
	loseScreen.setParent(&player);
	UpdateList::addNode(&loseScreen);

	//Spawn all enemies and rooms
	spawn(textures);

	//Run game engine
	UpdateList::startEngine("Temple of Pele");
	std::cout << "Done\n";
	return 0;
}
