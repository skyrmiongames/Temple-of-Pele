//SFML headers
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <string>

//Game headers
#include "UpdateList.h"
#include "GridMaker.h"
#include "TileMap.hpp"
#include "Player.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(600, 400), "SFML works!");
	sf::Clock clock;

	Textures *mainTextures = new Textures();
	Node::textures = mainTextures;

	//Load tile map
	GridMaker::build_grid();
	TileMap map;
    if (!map.load("resources/tileset.png", sf::Vector2u(32, 32), GridMaker::index_grid(), GridMaker::WIDTH, GridMaker::HEIGHT))
        return -1;

    //Set up player
    Player *player = new Player();
	player->setPosition(300, 200);
	UpdateList::add_node(player);

    //Run main window
	while (window.isOpen()) {
		//Check event updates
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			//if(event.type == sf::Event::KeyPressed)
			//	player->eightWayMovement();
			player->update(clock.getElapsedTime().asSeconds());

		}

		//Run base updates
		window.clear();
		window.draw(map);
		UpdateList::update(window);
		player->drawGUI(window);
		window.display();
	}

	return 0;
}