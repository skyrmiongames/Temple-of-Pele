#include "LogicComponents.hpp"
#include "Node.h"
#include "enums.h"

/*
 * Created by Stuart Irwin on 4/17/2019.
 * Nodes for activating other objects
 */

class AreaSwitch : public Node, public LogicSender {
private:
	CollisionLayer detecting;

public:
	//Area constructors
	AreaSwitch(CollisionLayer detecting=PLAYER) : Node(SWITCH) {
		this->detecting = detecting;
	}
	AreaSwitch(Vector2i *size, CollisionLayer detecting=PLAYER) : Node(size, SWITCH){
		this->detecting = detecting;
	}

	//Hide area
	bool get_hidden() {
		return true;
	}

	//Activate on collision
	void collide(Node *object) {
		if(object.get_layer() == detecting)
			send();
	}
}

class PressureSwitch : public Node, public LogicSender {
private:
	const CollisionLayer detecting;
	const int MAXTIME = 10;
	int timer = 0;

public:
	//Area constructors
	PressureSwitch(CollisionLayer detecting=PLAYER) : Node(SWITCH) {
		this->detecting = detecting;
	}

	//Show when active
	bool get_hidden() {
		return timer > 0;
	}

	//Activate on collision
	void collide(Node *object) {
		if(object.get_layer() == detecting) {
			send();
			timer = MAXTIME;
		}
	}

	//Deactivate on update
	void update() {
		if(timer > 0) {
			timer--;
			if(timer != MAXTIME)
				send();
		}
	}
}