#include "UpdateList.h"

/*
 * Created by Stuart Irwin on 4/17/2019.
 * Inserts nodes into UpdateList
 */

class NodeLoader : public LogicReciever {
private:
	std::vector<Node *> contents;

public:
	//Prepare node for adding
	void add_node(Node *next, sf::Vector2f position) {
		contents.push_back(next);
		next->setPosition(position * 16 + sf::Vector2f(8, 8));
	}

	//Add content nodes
	void activate() {
		for(Node *next : contents)
			UpdateList::add_node(next);
	}

	//One use only
	bool is_singleton() {
		return true;
	}
	~NodeLoader() {
		delete &contents;
	}
};