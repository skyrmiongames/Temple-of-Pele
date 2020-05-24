#include "UpdateList.h"

/*
 * Created by Stuart Irwin on 4/15/2019.
 * Manages layers of nodes through update cycle
 */

//Static variables
Node *(UpdateList::screen)[MAXLAYER];
std::bitset<MAXLAYER> UpdateList::nonCheckedLayers;
std::vector<Node *> UpdateList::deleted;
Node *UpdateList::camera = NULL;
sf::View UpdateList::viewPlayer;
bool running = true;
int count = 0;

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

//Set camera to follow node
void UpdateList::setCamera(Node *follow, sf::Vector2f size) {
	if(camera != NULL) {
		camera->setSize(sf::Vector2i(size.x,size.y));
		camera->setParent(follow);
	} else
		camera = new Node(0, sf::Vector2i(size.x,size.y), true, follow);
	viewPlayer.setSize(size);
}

void UpdateList::nonCheckedLayer(unsigned char layer) {
	if(layer >= MAXLAYER)
		throw new std::invalid_argument(LAYERERROR);
	nonCheckedLayers[layer] = true;
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
			if(nonCheckedLayers[layer] || source->checkCollision(camera)) {
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

	//Set camera position
	if(camera != NULL) {
		viewPlayer.setCenter(camera->getGPosition());
		window.setView(viewPlayer);
	}
}

//Seperate rendering thread
void renderingThread(std::string title, sf::VideoMode mode) {
	sf::RenderWindow window(mode, title);

	std::cout << "Thread starting\n";

    //Run rendering loop
	while(window.isOpen()) {
		//std::cout << "Draw\n";
		//Check event updates
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//Update window
		window.clear();
		UpdateList::draw(window);
		window.display();
	}

	std::cout << "Thread ending\n";

	running = false;
}

void startEngine(std::string title, sf::VideoMode mode) {
	//Set frame rate manager
	sf::Clock clock;
	double nextFrame = 0;

	std::thread rendering(renderingThread, title, mode);

	std::cout << "Starting\n";

    //Run main window
	while (running) {
		//Manage frame rate
		if(clock.getElapsedTime().asSeconds() >= nextFrame) {
			std::cout << "Update " << ++count << "\n";
			//Next update time
			nextFrame = clock.getElapsedTime().asSeconds() + .01;

			//Update nodes and sprites
			UpdateList::update(clock.getElapsedTime().asSeconds());
		}
	}

	rendering.join();
}
