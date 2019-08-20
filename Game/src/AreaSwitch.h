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

		//Set base texture
		setOrigin(8, 8);
	}

	//Hide area
	bool getHidden() {
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
	int nextTime = 0;
	bool hidden = false;

public:
	//Area constructors
	PressureSwitch(int delay, CollisionLayer detecting=PLAYER, sf::Vector2i size=sf::Vector2i(12, 12)) : Node(SWITCH, size) {
		this->delay = delay;
		this->detecting = detecting;

		//Set base texture
		setTexture(textures->plate);
		setOrigin(8, 8);
	}

	//Show when active
	bool get_hidden() {
		return hidden;
	}

	//Activate on collision
	void collide(Node *object, double time) {
		if(object->get_layer() == detecting) {
			if(nextTime <= time)
				send();

			nextTime = time + delay;
		}
	}

	//Deactivate on update
	void update(double time) {
		hidden = (nextTime > time);
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