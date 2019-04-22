#include "TileMap.hpp"
#pragma once

/*
 * Created by Stuart Irwin on 4/20/2019.
 * Show and run game end screen
 */

class EndScreen : public Node {
private:
	TileMap map;
	bool win;
	bool active = false;

	//Draw selected tilemap
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		if(active) {
			target.draw(map);
		}
    }

public:
	EndScreen(bool win) : Node(ENDSCREEN) {
		this->win = win;
		setTexture(Node::textures->exitLight);
	}

	void activate() {
		//Load text map file
		if(win)
			GridMaker::build_grid("resources/maps/win_text.txt");
		else
			GridMaker::build_grid("resources/maps/lose_text.txt");

		//Build tilemap
		map.load("resources/tiles/TileMap_Enviro.png", sf::Vector2u(16, 16), GridMaker::index_grid(), GridMaker::WIDTH, GridMaker::HEIGHT);
		map.setPosition(717, 0);

		active = true;
	}
};