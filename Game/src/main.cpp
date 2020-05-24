//SFML headers
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <string>
#include <thread>

//Game headers
#include "FullSpawner.hpp"
#include "engine/GridMaker.h"
#include "engine/AnimatedTileMap.hpp"

#include <X11/Xlib.h>

bool running = true;
sf::Vector2f Entity::playerPos;

void renderingThread(Player *player) {
	sf::RenderWindow window(sf::VideoMode(1200, 800), "Temple of Pele");

    //Run rendering loop
	while(window.isOpen()) {
		//Check event updates
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//Draw base map
		window.clear();

		//Draw general nodes
		UpdateList::draw(window);

		//Draw player gui and features
		player->drawGUI(window);
		player->drawView(window);

		//Confirm changes
		window.display();
	}

	running = false;
}

int main() {
	sf::Clock clock;
	XInitThreads();

	//Set texture loader
	Textures textures;

	//Mode variables
	FullSpawner spawner;
	std::string file = "resources/maps/full_map.txt";
	sf::Vector2f startPos = sf::Vector2f(456, 480);
	//startPos = sf::Vector2f(960, 176);

	//Load base tile map
	GridMaker::build_grid(file);
	TileMap map;
    if (!map.load("resources/tiles/TileMap_Enviro.png", sf::Vector2u(16, 16), GridMaker::index_grid(), GridMaker::WIDTH, GridMaker::HEIGHT))
        return -1;

    //Load animated tile map
	AnimatedTileMap aniMap;
    if (!aniMap.load("resources/tiles/TileMap_Gif.png", sf::Vector2u(16, 16), GridMaker::index_grid(true), GridMaker::WIDTH, GridMaker::HEIGHT, 12))
        return -1;

    UpdateList::addNode(&map);
    UpdateList::addNode(&aniMap);

    //Set up player
    Player player;
	player.setPosition(startPos);
	UpdateList::addNode(&player);

	//Set up selected room nodes
	spawner.spawn(textures);

	//Set frame rate manager
	double nextFrame = 0;

	//Start rendering thread
	std::thread rendering(renderingThread, &player);

    //Run main window
	while (running) {
		//Manage frame rate
		if(clock.getElapsedTime().asSeconds() >= nextFrame) {
			//Next update time
			nextFrame = clock.getElapsedTime().asSeconds() + .001;

			//Update nodes and sprites
			UpdateList::update(clock.getElapsedTime().asSeconds());
		}
	}

	return 0;
}