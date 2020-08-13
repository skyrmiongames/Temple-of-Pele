#include "UpdateList.h"

#define FRAME_DELAY sf::milliseconds(30)

/*
 * Created by Stuart Irwin on 4/15/2019.
 * Manages layers of nodes through update cycle
 */

//Static variables
Node *(UpdateList::screen)[MAXLAYER];
std::bitset<MAXLAYER> UpdateList::alwaysLoadedLayers;
std::vector<Node *> UpdateList::deleted;
Node *UpdateList::camera = NULL;
Node *UpdateList::pointer = NULL;
sf::View UpdateList::viewPlayer;
bool running = true;

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

//Remove all nodes in layer
void UpdateList::clearLayer(unsigned char layer) {
	if(layer >= MAXLAYER)
		throw new std::invalid_argument(LAYERERROR);

	Node *source = screen[layer];
	while(source != NULL) {
		source->setDelete();
		source = source->getNext();;
	}
}

//Set camera to follow node
Node *UpdateList::setCamera(Node *follow, sf::Vector2f size) {
	if(camera != NULL) {
		camera->setSize(sf::Vector2i(size.x,size.y));
		camera->setParent(follow);
	} else
		camera = new Node(0, sf::Vector2i(size.x,size.y), true, follow);
	viewPlayer.setSize(size);
	return camera;
}

void UpdateList::setPointer(Node *follow) {
	pointer = follow;
}

void UpdateList::alwaysLoadLayer(unsigned char layer) {
	if(layer >= MAXLAYER)
		throw new std::invalid_argument(LAYERERROR);
	alwaysLoadedLayers[layer] = true;
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
			if(alwaysLoadedLayers[layer] || source->checkCollision(camera)) {
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
	for(int layer = 0; layer < MAXLAYER; layer++) {
		Node *source = screen[layer];

		while(source != NULL) {
			if(!source->isHidden() &&
				(alwaysLoadedLayers[layer] || source->checkCollision(camera))) {
				//Check for parent node
				if(source->getParent() != NULL) {
					sf::Transform translation;
					translation.translate(source->getParent()->getGPosition());
					window.draw(*source, translation);
				} else
					window.draw(*source);
			}
			source = source->getNext();
		}
	}
}

//Seperate rendering thread
void UpdateList::renderingThread(std::string title, sf::VideoMode mode) {
	//Set frame rate manager
	sf::Clock clock;
	sf::Time nextFrame = clock.getElapsedTime();

	std::cout << "Thread starting\n";
	sf::RenderWindow window(mode, title);

    //Run rendering loop
	while(window.isOpen()) {
		//Check event updates
		sf::Event event;
		while(window.pollEvent(event)) {
			if(event.type == sf::Event::Closed)
				window.close();
		}

		sf::Time time = clock.getElapsedTime();
		if(time >= nextFrame) {
			//Next update time
			nextFrame = time + FRAME_DELAY;

			//Set pointer position
			if(pointer != NULL) {
				sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
				pointer->setPosition(mousePos);
			}

			//Update window
			window.clear();
			UpdateList::draw(window);

			//Set camera position
			if(camera != NULL) {
				viewPlayer.setCenter(camera->getGPosition());
				window.setView(viewPlayer);
			}

			window.display();
		}
		time = clock.getElapsedTime();
		std::this_thread::sleep_for(
			std::chrono::microseconds((nextFrame - time).asMicroseconds()));
	}

	std::cout << "Thread ending\n";

	running = false;
}

void UpdateList::startEngine(std::string title, sf::VideoMode mode) {
	//Set frame rate manager
	sf::Clock clock;

	std::thread rendering(UpdateList::renderingThread, title, mode);
	sf::Time nextFrame = clock.getElapsedTime() + FRAME_DELAY;

	std::cout << "Starting\n";

	//Initial update
	for(Node *layer : screen) {
		Node *source = layer;

		while(source != NULL) {
			source->update(0);
			source = source->getNext();
		}
	}

    //Run main window
	while (running) {
		//Manage frame rate
		sf::Time time = clock.getElapsedTime();
		if(time >= nextFrame) {
			//Next update time
			nextFrame = time + FRAME_DELAY;

			//Update nodes and sprites
			UpdateList::update(time.asSeconds());
		}
		time = clock.getElapsedTime();
		std::this_thread::sleep_for(
			std::chrono::microseconds((nextFrame - time).asMicroseconds()));
	}

	rendering.join();
}
