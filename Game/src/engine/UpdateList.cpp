#include "UpdateList.h"

/*
 * Created by Stuart Irwin on 4/15/2019.
 * Manages layers of nodes through update cycle
 */

//Static variables
Node *(UpdateList::screen)[MAXLAYER];
std::vector<Node *> UpdateList::deleted;

//Add node to update cycle
void UpdateList::addNode(Node *next) {
	unsigned char layer = next->getLayer();
	if(layer >= MAXLAYER)
		throw new std::invalid_argument(LAYERERROR);
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
			screen[layer] = source;
		}

		//For each node in layer order
		while(source != NULL) {
			//Check each selected collision layer
			int collisionLayer = 0;
			for(int i = 0; i < (int)source->getCollisionLayers().count(); i++) {
				while(!source->getCollisionLayer(collisionLayer))
					collisionLayer++;

				//Check collision box of each node
				Node *other = screen[collisionLayer];
				while(other != NULL) {
					if(other != source && source->checkCollision(other))
						source->collide(other, time);
					other = other->getNext();
				}
				collisionLayer++;
			}

			//Update each object
			source->update(time);

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
	std::vector<Node *>::iterator it = deleted.begin();
	while(it != deleted.end()) {
		Node *node = *it;
		it++;
		delete node;
	}
	deleted.clear();


	//Render each node in order
	for(Node *layer : screen) {
		Node *source = layer;

		while(source != NULL) {
			if(!source->isHidden()) {
				//Check for parent node
				if(source->getParent() != NULL) {
					sf::Transform translation;
					translation.translate(source->getParent()->getPosition());
					window.draw(*source, translation);
				} else
					window.draw(*source);
			}
			source = source->getNext();
		}
	}
}
