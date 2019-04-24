//SFML headers
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <string>

//Game headers
#include "TestSpawner.hpp"
#include "FullSpawner.hpp"
#include "GridMaker.h"
#include "AnimatedTileMap.hpp"

int main() {
	bool testMode = false;

	//Start game window
	sf::RenderWindow window(sf::VideoMode(1200, 800), "Temple of Pele");
	sf::Clock clock;

	//Set texture loader
	Textures *mainTextures = new Textures();
	Node::textures = mainTextures;

	//Mode variables
	NodeSpawner *spawner = new FullSpawner();
	std::string file = "resources/maps/full_map.txt";
	sf::Vector2f startPos = sf::Vector2f(600, 480);
	startPos = sf::Vector2f(1104, 176);

	//Set test mode
	if(testMode) {
		spawner = new TestSpawner();
		file = "resources/maps/test_map.txt";
		startPos = sf::Vector2f(112, 80);
	}

	//Load tile map
	GridMaker::build_grid(file);
	TileMap map;
    if (!map.load("resources/tiles/TileMap_Enviro.png", sf::Vector2u(16, 16), GridMaker::index_grid(), GridMaker::WIDTH, GridMaker::HEIGHT))
        return -1;

    //Load animated tile map
	AnimatedTileMap aniMap;
    if (!aniMap.load("resources/tiles/TileMap_Gif.png", sf::Vector2u(16, 16), GridMaker::index_grid(true), 12))
        return -1;

    //Set up player
    Player *player = new Player();
	player->setPosition(startPos);
	UpdateList::add_node(player);

	//Set up test room nodes
	spawner->spawn();

    //Run main window
	while (window.isOpen()) {
		//Check event updates
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();

		}

		//Locate player
		Node::playerPos = player->getPosition();

		//Draw base map
		window.clear();
		window.draw(map);

		//Draw animated map
		aniMap.update(clock.getElapsedTime().asSeconds());
		window.draw(aniMap);

		//Draw nodes and sprites
		UpdateList::update(window, clock.getElapsedTime().asSeconds());

		//Player updates
		player->drawGUI(window);
		player->drawView(window);
		player->animatePlayer(clock.getElapsedTime().asSeconds());

		window.display();
	}

	return 0;
}