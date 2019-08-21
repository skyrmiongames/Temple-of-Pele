#include "UpdateList.h"

/*
 * Created by Stuart Irwin on 4/15/2019.
 * Manages layers of nodes through update cycle
 */

//Static variables
Node (*UpdateList::screen)[MAXLAYER];
std::vector<Node *> UpdateList::deleted;

//Add node to update cycle
void UpdateList::addNode(unsigned char layer, Node *next) {
	if(layer >= MAXLAYER)
		throw new invalid_argument(LAYERERROR);
	if(screen[layer] == NULL)
		screen[layer] = next;
	else 
		screen[layer]->addNode(next);
}

//Update all nodes in list
void UpdateList::update(double time) {
	//Check collisions and updates
	for(int layer = 0; layer < MAXLAYER; layer++) {
		Node *source = screen[layer];

		//Check first node for deletion
		if(source != NULL && source->isDeleted()) {
			deleted.push_back(source);
			source = source->getNext();
			screen[layer] = source
		}

		//For each node in layer order
		while(source != NULL) {
			if(!source->isHidden()) {

				//Check each selected collision layer
				int collisionLayer = 0;
				for(int i = 0; i < source->getCollisionLayer().count; i++) {
					while(!source->getCollisionLayer(collisionLayer))
						collisionLayer++;

					//Check collision box of each node
					for(Node *other : screen[collisionLayer]) {
						if(other != source && source->check_collision(other)) {
							source->collide(other, time);
						}
					}
					collisionLayer++;
				}

				//Update each object
				source->update(time);
			}

			//Check next node for deletion
			if(source->getNext() != NULL && source->getNext()->isDeleted()) {
				deleted.push_back(source->getNext());
				source->deleteNext();
			}

			source = source->getNext();
		}
	}
}

//Thread safe draw nodes in list
void UpdateList::draw(sf::RenderWindow &window) {
	//Loop through list to delete
	std::vector<Node *>::iterator it = deleting->begin();
	while(it != list->end()) {
		Node *node = *it;
		it++;
		delete node;
	}
	deleting->clear();


	//Render each node in order
	for(Node *layer : screen) {
		Node *source = layer;

		while(source != NULL) {
			if(!source->isHidden())
				window.draw(*source);
			source = source->getNext();
		}
	}
}
