#include "Skyrmion/Node.h"

/*
 * Created by Stuart Irwin on 4/19/2019.
 * Small key that can be picked up
 */

class Key : public Node {
public:
	Key(Textures &textures) : Node(KEY) {
		setTexture(textures.key);
	}
};