#include "TileMap.hpp"

/*
 * Created by Stuart Irwin on 4/20/2019.
 * Show and run game end screen
 */

class EndScreen : public sf::Drawable, public sf::Transformable {
private:
	TileMap map;
	sf::View viewPlayer;

	//Draw selected tilemap
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(map);
		window.setView(viewPlayer);
    }

public:
	EndScreen(bool win) {
		//Load text map file
		if(win)
			GridMaker::build_grid("resources/maps/win_text.txt");
		else
			GridMaker::build_grid("resources/maps/lose_text.txt");

		//Build tilemap
		map.load("resources/tiles/TileMap_Enviro.png", sf::Vector2u(16, 16), GridMaker::index_grid(), 38, 9);
		setPosition(-100, -100);

		//Set up viewport
		viewPlayer.setSize(sf::Vector2f(300, 200));
		viewPlayer.setCenter(sf::Vector2f(-100, -100));
	}
}