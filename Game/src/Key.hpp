#include "engine/Node.h"

/*
 * Created by Stuart Irwin on 4/19/2019.
 * Small key that can be picked up
 */

class Key : public Node {
public:
	Key(Textures &textures) : Node(KEY) {
		setTexture(textures.key);
	}

	//One use thing
	UseAmount is_singleton() {
		return SINGLE;
	}

	//Delete key when picked up
	void activate() {
		setDelete();
	}
};