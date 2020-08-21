#include "Skyrmion/TileMap.hpp"
#include "Skyrmion/LightMap.hpp"
#include "indexes.h"
#include "textures.h"
#pragma once

/*
 * Created by Stuart Irwin on 4/20/2019.
 * Show and run game end screen
 */

class EndScreen : public Node {
private:
	TileMap *map;
	LightMap *lighting;
	bool win;
	bool active = false;

	//Draw selected tilemap
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		if(active && map != NULL)
			target.draw(*map);
    }

public:
	EndScreen(LightMap *lighting, bool win) : Node(win ? ENDSCREEN : DEATH) {
		this->win = win;
		this->lighting = lighting;
	}

	void display() {
		//Load text map file
		GridMaker grid("resources/maps/win_text.txt", 42, 19);
		if(!win)
			grid.reload("resources/maps/lose_text.txt");

		//Build tilemap
		map = new TileMap("resources/tiles/TileMap_Enviro.png", 16, 16, Indexer(&grid, displayIndex, 1));
		map->setPosition(0, 0);
		//setPosition(2000, 0);
		setRotation(0);
		UpdateList::alwaysLoadLayer(getLayer());

		lighting->setHidden(true);
		active = true;
	}
};