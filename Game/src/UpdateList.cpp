#include "UpdateList.h"

/*
 * Created by Stuart Irwin on 4/15/2019.
 * Manages list of nodes through update cycle
 */

//Static variables
std::vector<Node *> UpdateList::screen;
std::vector<Node *> UpdateList::added;
std::vector<Node *> UpdateList::deleted;
std::vector<Node *> UpdateList::rendering;
bool UpdateList::lock;

//Check if node has moving collisionlayer
bool UpdateList::moving_layer(Node *n) {
	return n->get_layer() == PLAYER || n->get_layer() == ENEMY || n->get_layer() == FIREBALL;
}

//Add node to update cycle
void UpdateList::add_node(Node *next) {
	added.push_back(next);
}

//Remove marked nodes from update cycle
void UpdateList::remove_nodes(std::vector<Node *> *list, std::vector<Node *> *deleting, bool permanent) {
	std::vector<Node *>::iterator it = list->begin();
	std::vector<Node *>::iterator remove = deleting->begin();

	//Loop through list
	while(it != list->end()) {
		bool removing = false;

		//Check for delete mark
		if(*it == *remove) {
			removing = true;

			Node *node = *it;
			it = list->erase(it);
			if(permanent)
				delete node;
		}

		//Move to next
		if(!removing && it != list->end()) it++;
		if(removing && remove != deleting->end()) remove++;
	}

	deleting->clear();
}

//Update all nodes in list
void UpdateList::update(double time) {
	std::vector<Node *> deleting;

	//Check collisions and updates
	for(Node *source : screen) {
		if(source->on_screen()) {
			//For moving object types
			if(moving_layer(source)) {
				for(Node *object : screen) {
					//Actually check collision box
					if(object != source && source->check_collision(object)) {
						source->collide(object, time);

						//Check for double detection
						if(!moving_layer(object))
							object->collide(source, time);
					}
				}
			}

			//Update each object
			source->update(time);
		}

		//Check for deletion
		if(source->get_delete()) {
			deleted.push_back(source);
			deleting.push_back(source);
		}
	}

	//Remove deleted nodes
	lock = true;
	if(!deleting.empty())
		remove_nodes(&screen, &deleting, false);

	//Add new nodes
	if(!added.empty()) {
		screen.insert(screen.end(), added.begin(), added.end());
		added.clear();
	}
	lock = false;
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
