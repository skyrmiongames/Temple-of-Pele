#include "Skyrmion/UpdateList.h"
#include "Logic/LogicComponents.h"
#include "textures.h"

/*
 * Created by Stuart Irwin on 4/17/2019.
 * Inserts nodes into UpdateList
 */

class NodeLoader : public LogicReciever {
private:
	std::vector<Node *> contents;

public:
	//Prepare node for adding
	void add_node(Node *next, int x, int y) {
		contents.push_back(next);

		//Set proper node position
		next->setPosition(x * 16 - 8, y * 16 - 8);
	}

	//Add content nodes
	void activate() {
		for(Node *next : contents)
			UpdateList::addNode(next);
	}

	//One use only
	RecivingAction getRecivingAction() { return DELETE; };

	//Full delete
	~NodeLoader() {
		contents.clear();
	}
};

void spawn(Textures &textures);