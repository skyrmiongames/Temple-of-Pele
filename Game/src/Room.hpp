#include <list>
#include "UpdateList.hpp"
#include "Node.h"

/*
 * Created by Stuart Irwin on 4/13/2019.
 * Loads set of nodes together
 */

class Room {
private:
	std::list<Node> contents;

public:
	//Build room contents
	Room(std::string file);

	//Add contents to game
	void initialize() {
		for(Node n : contents) {
			UpdateList.add_node(n);
			n.on_load();
		}
	}
};