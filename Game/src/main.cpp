//SFML headers
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <string>
#include <thread>

//Game headers
#include "TestSpawner.hpp"
#include "FullSpawner.hpp"
#include "GridMaker.h"
#include "AnimatedTileMap.hpp"

//X11 multithreading
#include <X11/Xlib.h>

void renderingThread(sf::RenderWindow *window, Player *player, TileMap *map, AnimatedTileMap *aniMap) {
    //Run rendering loop
	while(window->isOpen()) {
		//Draw base map
		window->clear();
		window->draw(*map);
		window->draw(*aniMap);

		//Draw general nodes
		UpdateList::draw(*window);

		//Draw player gui and features
		player->drawGUI(*window);
		player->drawView(*window);

		//Confirm changes
		window->display();
	}
}

int main() {
	bool testMode = false;

	//Start game window
	XInitThreads();
	sf::RenderWindow window(sf::VideoMode(1200, 800), "Temple of Pele");
	sf::Clock clock;

	//Set texture loader
	Textures *mainTextures = new Textures();
	Node::textures = mainTextures;

	//Mode variables
	NodeSpawner *spawner = new FullSpawner();
	std::string file = "resources/maps/full_map.txt";
	sf::Vector2f startPos = sf::Vector2f(456, 480);
	//startPos = sf::Vector2f(960, 176);

	//Set test mode
	if(testMode) {
		spawner = new TestSpawner();
		file = "resources/maps/test_map.txt";
		startPos = sf::Vector2f(112, 80);
	}

	//Load base tile map
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

	//Set up selected room nodes
	spawner->spawn();

	//Set frame rate manager
	double nextFrame = 0;

	//Start rendering thread
	std::thread rendering(renderingThread, &window, player, &map, &aniMap);

    //Run main window
	while (window.isOpen()) {
		//Check event updates
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//Manage frame rate
		if(clock.getElapsedTime().asSeconds() >= nextFrame) {
			//Next update time
			nextFrame = clock.getElapsedTime().asSeconds() + .001;

			//Locate player
			Node::playerPos = player->getPosition();

			//Update nodes and sprites
			UpdateList::update(clock.getElapsedTime().asSeconds());

			//Update other graphics
			aniMap.update(clock.getElapsedTime().asSeconds());
			player->animatePlayer(clock.getElapsedTime().asSeconds());
		}
	}

	return 0;
}