#include "../../Game/src/Node.h"

/*
 * Created by Stuart Irwin on 4/24/2019.
 * Node to return tests and checks
 */

namespace Tests {
	class TestNode : public Node {
	public:
		bool collided = false;
		bool updated = false;

		TestNode() : Node(PLAYER) {}

		void update(double time) {
			updated = true;
		}

		void collide(Node *object) {
			updated = true;
		}
	};
}