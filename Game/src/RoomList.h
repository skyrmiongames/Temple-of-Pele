#include <SFML/Graphics/Rect.hpp>
#include "Node.h"
#include "Room.h"

/*
 * Created by Stuart Irwin on 4/13/2019.
 * Manages list of rooms through update cycle
 */

class RoomList {
private:
	const int SIZE = 1;
	(Room*)[] rooms = new Room[SIZE];

public:
	RoomList();

}