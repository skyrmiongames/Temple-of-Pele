//SFML headers
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <string>

//Game headers
#include "TestNodes.hpp"
#include "GridMaker.h"
#include "AnimatedTileMap.hpp"
#include "Player.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(1200, 800), "Temple of Pele");
	sf::Clock clock;

	Textures *mainTextures = new Textures();
	Node::textures = mainTextures;

	//Load tile map
	GridMaker::build_grid("resources/maps/test_map.txt");
	TileMap map;
    if (!map.load("resources/tiles/TileMap_Enviro.png", sf::Vector2u(16, 16), GridMaker::index_grid(), GridMaker::WIDTH, GridMaker::HEIGHT))
        return -1;

    //Load animated tile map
	AnimatedTileMap aniMap;
    if (!aniMap.load("resources/tiles/TileMap_Gif.png", sf::Vector2u(16, 16), GridMaker::index_grid(true), 12))
        return -1;

    //Set up player
    Player *player = new Player();
	player->setPosition(128, 64);
	UpdateList::add_node(player);

	//Set up test room nodes
	TestNodes::test_nodes();

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
		player->drawGUI(window);
		player->drawView(window);
		player->animatePlayer(clock.getElapsedTime().asSeconds());

		window.display();
	}

	return 0;
}