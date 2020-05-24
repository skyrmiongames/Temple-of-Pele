#include "engine/TileMap.hpp"
#include "engine/LogicComponents.h"
#include "textures.h"
#pragma once

/*
 * Created by Stuart Irwin on 4/20/2019.
 * Show and run game end screen
 */

class EndScreen : public Node {
private:
	sf::Sprite *light;
	TileMap map;
	bool win;
	bool active = false;

	//Draw selected tilemap
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		if(active) {
			//Draw end text map
			target.draw(map);
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
		if(win)
			GridMaker::build_grid("resources/maps/win_text.txt");
		else
			GridMaker::build_grid("resources/maps/lose_text.txt");

		//Build tilemap
		map.load("resources/tiles/TileMap_Enviro.png", sf::Vector2u(16, 16), GridMaker::index_grid(), GridMaker::WIDTH, GridMaker::HEIGHT);
		map.setPosition(1715, 0);
		setPosition(2000, 0);
		setRotation(0);

		active = true;
	}
};