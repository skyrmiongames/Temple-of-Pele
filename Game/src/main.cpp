//SFML headers
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <string>
#include "GridMaker.h"
#include "TileMap.hpp"

int main() {
	sf::RenderWindow window(sf::VideoMode(600, 400), "SFML works!");

	//Load tile map
	GridMaker::build_grid();
	TileMap map;
    if (!map.load("resources/tileset.png", sf::Vector2u(32, 32), GridMaker::index_grid(), GridMaker::SIZE, GridMaker::SIZE))
        return -1;

    //Run main window
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(map);
		window.display();
	}

	return 0;
}