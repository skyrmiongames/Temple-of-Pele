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
	void add_node(Node *next, int x, int y) {
		contents.push_back(next);
		next->setPosition(x * 16, y * 16);
	}

	//Add content nodes
	void activate() {
		for(Node *next : contents)
			UpdateList::add_node(next);
	}

	//One use only
	UseAmount is_singleton() {
		return DELETE;
	}

	//Full delete
	~NodeLoader() {
		contents.clear();
	}
};