#include "Skyrmion/tiling/TileMap.hpp"
#include "Skyrmion/tiling/LightMap.h"
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
	bool win;
	bool active = false;

	//Draw selected tilemap
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		if(active && map != NULL)
			target.draw(*map);
    }

public:
	EndScreen(bool win) : Node(win ? ENDSCREEN : DEATH) {
		this->win = win;
	}

	void display(Textures *textures) {
		//Load text map file
		GridMaker grid("resources/maps/win_text.txt");
		if(!win)
			grid.reload("resources/maps/lose_text.txt");

		//Build tilemap
		map = new TileMap(&textures->environment, 16, 16, new MapIndexer(&grid, displayIndex, 1), getLayer(), 0);
		map->setPosition(0, 0);
		//setPosition(2000, 0);
		setRotation(0);
		UpdateList::staticLayer(getLayer());
		UpdateList::hideLayer(LIGHTING);
		active = true;
	}
};