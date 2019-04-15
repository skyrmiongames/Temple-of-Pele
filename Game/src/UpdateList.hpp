#include <string>
#include <list>
#include "Node.h"
#include "Room.h"

/*
 * Created by Stuart Irwin on 4/13/2019.
 * Manages list of nodes through update cycle
 */

class UpdateList {
private:
	static std::list<Node> onScreen = new list();
	static std::list<Node> offScreen = new list();
	static bool check_screen = true;

public:
	//Add node to update cycle
	static void add_node(Node next) {
		nodes.push_front(next);
		check_screen = true;
	}

	//Remove node from update cycle
	static void remove_node(Node extra) {
		nodes.remove(extra);
		check_screen = true;
	}

	static void update_lists() {
		//Confirm nodes on screen
		for(Node n : onScreen) {
			if(!n.on_screen()) {
				offScreen.push_front(n);
				onScreen.remove(n);
			}
		}

		//Confirm nodes off screen
		for(Node n : offScreen) {
			if(n.on_screen()) {
				onScreen.push_front(n);
				offScreen.remove(n);
			}
		}
	}

	//Check if node has moving collisionlayer
	bool moving_layer(Node n) {
		return n.get_layer() == PLAYER || n.get_layer() == ENEMY;
	}

	//Update all nodes in list
	static void update() {
		if(check_screen)
			update_lists();

		//Check collisions and updates
		for(Node source : onScreen) {
			//For moving object types
			if(moving_layer(source)) {
				for(Node object : onScreen) {
					//Actually check collision box
					if(source.check_collision(object)) {
						source.collision(object);

						//Check for double detection
						if(!moving_layer(object))
							object.collision(source);
					}
				}
			}

			//Update each object
			source.update();
		}
	}
};