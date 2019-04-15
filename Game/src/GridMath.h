#include "enums.h"

/*
 * Created by Stuart Irwin on 4/13/2019.
 * Generates and stores main tilemap
 */

class GridMath {
private:
	static char[][] tiles;

public:
	static void build_grid();
	
	//Retrieve tile properties
	static void char get_tile(sf::Vector2i position);
	static void TileType check_tile(sf::Vector2i position);
};