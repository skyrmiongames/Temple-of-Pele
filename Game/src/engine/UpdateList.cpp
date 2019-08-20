#include "UpdateList.h"

/*
 * Created by Stuart Irwin on 4/15/2019.
 * Manages list of nodes through update cycle
 */

//Static variables
Node **UpdateList::screen;
Node **UpdateList::deleted;

//Add node to update cycle
void UpdateList::add_node(unsigned int layer, Node *next) {
	
}

//Update all nodes in list
void UpdateList::update(double time) {

	//Check collisions and updates
	while(Node *source : screen) {
		if(!source->isHidden()) {
			//For moving object types
			if(source->isCollidible()) {
				for(Node *object : screen) {
					//Actually check collision box
					if(object->isCollidible() && object != source && source->check_collision(object)) {
						source->collide(object, time);
					}
				}
			}

			//Update each object
			source->update(time);
		}

		//Check for deletion
		if(source->get_delete()) {
			deleted.push_back(source);
		}
	}

	//Add new nodes
	if(!added.empty()) {
		screen.insert(screen.end(), added.begin(), added.end());
		added.clear();
	}
}

//Thread safe draw nodes in list
void UpdateList::draw(sf::RenderWindow &window) {
	//Update list safely
	if(lock == false)
		rendering = screen;

	//Delete nodes safely
	if(!deleted.empty())
		remove_nodes(&rendering, &deleted, true);

	//Render each node
	for(Node *source : rendering) {
		if(!source->get_hidden() && source->on_screen())
			window.draw(*source);
	}
}
