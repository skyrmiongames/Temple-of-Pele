#include "UpdateList.h"

/*
 * Created by Stuart Irwin on 4/15/2019.
 * Manages list of nodes through update cycle
 */

//Static variables
std::vector<Node *> UpdateList::onScreen;
std::vector<Node *> UpdateList::offScreen;
bool UpdateList::checking_screen;

//Sort nodes by on screen
void UpdateList::update_lists() {
	//Confirm nodes on screen
	for(std::vector<Node*>::iterator it = onScreen.begin() ; it != onScreen.end(); ++it) {
		if(!(*it)->on_screen()) {
			offScreen.push_back(*it);
			onScreen.erase(it);
		}
	}

	//Confirm nodes off screen
	for(std::vector<Node*>::iterator it = offScreen.begin() ; it != offScreen.end(); ++it) {
		if(!(*it)->on_screen()) {
			onScreen.push_back(*it);
			offScreen.erase(it);
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
	onScreen.push_back(next);
	checking_screen = true;
}

//Remove marked nodes from update cycle
void UpdateList::remove_nodes() {
	for(std::vector<Node*>::iterator it = onScreen.begin() ; it != onScreen.end(); ++it) {
		if((*it)->get_delete()) {
			onScreen.erase(it);
			delete *it;
			return;
		}
	}
	for(std::vector<Node*>::iterator it = offScreen.begin() ; it != offScreen.end(); ++it) {
		if((*it)->get_delete()) {
			offScreen.erase(it);
			delete *it;
			return;
		}
	}
}

//Schedule screen list update on next cycle
void UpdateList::check_screen() {
	checking_screen = true;
} 

//Update all nodes in list
void UpdateList::update(sf::RenderWindow &window, double time) {
	bool deleting = false;

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
		source->update(time);
		if(!source->get_hidden())
			window.draw(*source);

		//Check for deletion
		if(source->get_delete())
			deleting = true;
	}

	if(deleting)
		remove_nodes();
}
