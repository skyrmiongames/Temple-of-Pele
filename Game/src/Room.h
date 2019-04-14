#include <list>
#include "TileMap.hpp"

/*
 * Created by Stuart Irwin on 4/13/2019.
 * Stores room contents and updates
 */

class Room {
private:
	int index;
	TileMap tiles;

public:
	Room(int i);

	//Setup
	void load();
	void enter();
};