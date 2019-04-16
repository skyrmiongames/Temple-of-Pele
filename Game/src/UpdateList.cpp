#include "UpdateList.h"

/*
 * Created by Stuart Irwin on 4/15/2019.
 * Manages list of nodes through update cycle
 */

//Static variables
std::list<Node*> UpdateList::onScreen;
std::list<Node*> UpdateList::offScreen;

//Sort nodes by on screen
void UpdateList::update_lists() {
	//Confirm nodes on screen
	for(Node *n : onScreen) {
		if(!n->on_screen()) {
			offScreen.push_front(n);
			onScreen.remove(n);
		}
	}

	//Confirm nodes off screen
	for(Node *n : offScreen) {
		if(n->on_screen()) {
			onScreen.push_front(n);
			offScreen.remove(n);
		}
	}

	checking_screen = false;
}

//Check if node has moving collisionlayer
bool UpdateList::moving_layer(Node *n) {
	return n->get_layer() == PLAYER || n->get_layer() == ENEMY;
}

//Add node to update cycle
void UpdateList::add_node(Node *next) {
	offScreen.push_front(next);
	checking_screen = true;
}

//Remove node from update cycle
void UpdateList::remove_node(Node *extra) {
	offScreen.remove(extra);
	onScreen.remove(extra);
}

//Schedule screen list update on next cycle
void UpdateList::check_screen() {
	checking_screen = true;
} 

//Update all nodes in list
void UpdateList::update() {
	if(checking_screen)
		update_lists();

	//Check collisions and updates
	for(Node *source : onScreen) {
		//For moving object types
		if(moving_layer(source)) {
			for(Node *object : onScreen) {
				//Actually check collision box
				if(source->check_collision(object)) {
					source->collide(object);

					//Check for double detection
					if(!moving_layer(object))
						object->collide(source);
				}
			}
		}

		//Update each object
		source->update();
	}
}
