//SFML headers
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

//Game headers
#include "Skyrmion/tiling/TileMap.hpp"
#include "Skyrmion/tiling/LightMap.h"
#include "Skyrmion/tiling/TileFilters.hpp"
#include "NodeLoader.hpp"
#include "Player.h"

sf::Vector2f Entity::playerPos;
MapIndexer *Entity::mazeIndex;
MapIndexer *Entity::mazeFireballIndex;
LightMap *Entity::lighting;

int main() {
	//Load settings file
	Settings::loadSettings("resources/settings.json");
	Textures textures;

	//Load base tile maps
	GridMaker grid("resources/maps/full_map.txt");
	TileMap map(&textures.environment, 16, 16, new MapIndexer(&grid, displayIndex, 1), MAP);
	AnimatedTileMap aniMap(&textures.animated, 16, 16, new MapIndexer(&grid, animatedIndex, -1), 12, 0.3, MAP);
	TileMap quadMap(&textures.environment, 16, 16,
		new QuadIndexer(new MapIndexer(&grid, quadPreprocessIndex, -1), quadIndex, -1), MAP);
	quadMap.setPosition(8,8);
	Entity::mazeIndex = new MapIndexer(&grid, collisionIndex, EMPTY, 16, 16);
	Entity::mazeFireballIndex = new MapIndexer(&grid, fireballCollisionIndex, EMPTY, 16, 16);

	//Create test Light map
	MapIndexer lightMap(&grid, lightIndex, 0, 2, 2);
	LightMapCollection lighting(16, 16, &lightMap, LIGHTING);
	LightMap staticLighting(16, 16, 0.2, 0.2, &lightMap, LIGHTING, true);
	LightMap fireballLighting(16, 16, 0.2, 0.2, &lightMap, LIGHTING, false);
	lighting.addLightMap(&staticLighting);
	lighting.addLightMap(&fireballLighting);
	UpdateList::addNode(&lighting);
	Entity::lighting = &fireballLighting;

    //Link tilemaps
    UpdateList::addNode(&map);
    UpdateList::addNode(&aniMap);
    UpdateList::addNode(&quadMap);

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
