#include "Skyrmion/TileMap.hpp"
#include "LogicComponents.h"
#include "indexes.h"
#include "textures.h"
#pragma once

/*
 * Created by Stuart Irwin on 4/20/2019.
 * Show and run game end screen
 */

class EndScreen : public Node {
private:
	sf::Sprite *light;
	TileMap *map;
	bool win;
	bool active = false;

	//Draw selected tilemap
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		if(active && map != NULL) {
			//Draw end text map
			target.draw(*map);
		} else {
			light->setPosition(getPosition());
			target.draw(*light);
		}
    }

public:
	EndScreen(Textures &textures, bool win) : Node(ENDSCREEN) {
		this->win = win;

		//Build sprite for light effect
		light = new sf::Sprite();
		light->setRotation(-90);
		light->setTexture(textures.exitLight);
		light->setOrigin(8, 8);
	}

	void display() {
		//Load text map file
		GridMaker grid("resources/maps/win_text.txt", 42, 19);
		if(!win)
			grid.reload("resources/maps/lose_text.txt");

		//Build tilemap
		map = new TileMap("resources/tiles/TileMap_Enviro.png", 16, 16, Indexer(&grid, displayIndex, 1));
		map->setPosition(1715, 0);
		setPosition(2000, 0);
		setRotation(0);

		active = true;
	}
};