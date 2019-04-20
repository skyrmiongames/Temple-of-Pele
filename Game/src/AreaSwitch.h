#include "LogicComponents.h"
#include "Node.h"
#include "enums.h"

/*
 * Created by Stuart Irwin on 4/17/2019.
 * Nodes to detect entities within area
 */

class AreaSwitch : public Node, public LogicSender {
private:
	CollisionLayer detecting;
	bool hidden;

public:
	//Area constructors
	AreaSwitch(bool hidden=true, CollisionLayer detecting=PLAYER, sf::Vector2i size=sf::Vector2i(12, 12)) : Node(SWITCH, size){
		this->detecting = detecting;
		this->hidden = hidden;
		setTexture(textures->plate);
	}

	//Hide area
	bool get_hidden() {
		return hidden;
	}

	//Activate on collision
	void collide(Node *object) {
		if(object->get_layer() == detecting) {
			//Send and delete
			send();
			set_delete();
		}
	}
};

class PressureSwitch : public Node, public LogicSender {
private:
	int delay;
	CollisionLayer detecting;
	int timer = 0;

public:
	//Area constructors
	PressureSwitch(int delay, CollisionLayer detecting=PLAYER) : Node(SWITCH) {
		this->delay = delay;
		this->detecting = detecting;
		setTexture(textures->plate);
	}

	//Show when active
	bool get_hidden() {
		return timer > 0;
	}

	//Activate on collision
	void collide(Node *object) {
		if(object->get_layer() == detecting) {
			send();
			timer = delay;
		}
	}

	//Deactivate on update
	void update(double time) {
		if(timer > 0)
			timer--;
	}
};

class EmptySwitch : public Node, public LogicSender {
private:
	CollisionLayer detecting;
	int collisionTime;

public:
	//Area constructors
	EmptySwitch(CollisionLayer detecting=ENEMY, sf::Vector2i size=sf::Vector2i(16, 16)) : Node(SWITCH, size){
		this->detecting = detecting;
	}

	//Hide area
	bool get_hidden() {
		return true;
	}

	//Reset on collision
	void collide(Node *object) {
		if(object->get_layer() == detecting)
			collisionTime = 0;
	}

	//Wait for multiple updates
	void update(double time) {
		collisionTime++;

		//Send and delete
		if(collisionTime >= 5) {
			send();
			set_delete();
		}

	}
};