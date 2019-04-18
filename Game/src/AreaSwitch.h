#include "LogicComponents.h"
#include "Node.h"
#include "enums.h"

/*
 * Created by Stuart Irwin on 4/17/2019.
 * Nodes for activating other objects
 */

class AreaSwitch : public Node, public LogicSender {
private:
	CollisionLayer detecting;
	bool single;

public:
	//Area constructors
	AreaSwitch(bool single=true, sf::Vector2i size=sf::Vector2i(16, 16), CollisionLayer detecting=PLAYER) : Node(SWITCH, size){
		this->detecting = detecting;
		this->single = single;
		setTexture(textures->Knife);
	}

	//Hide area
	bool get_hidden() {
		return false;
	}

	//Set single use
	bool is_singleton() {
		return true;
	}

	//Activate on collision
	void collide(Node *object) {
		if(object->get_layer() == detecting)
			send();
	}
};

class PressureSwitch : public Node, public LogicSender {
private:
	const int MAXTIME = 10;
	CollisionLayer detecting;
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
		if(object->get_layer() == detecting) {
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
};