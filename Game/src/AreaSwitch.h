#include "engine/LogicComponents.h"
#include "engine/Node.h"
#include "enums.h"
#include "textures.h"

/*
 * Created by Stuart Irwin on 4/17/2019.
 * Nodes to detect entities within area
 */

class AreaSwitch : public Node, public LogicSender {
public:
	//Area constructors
	AreaSwitch(bool hidden=true, CollisionLayer detecting=PLAYER, sf::Vector2i size=sf::Vector2i(12, 12)) : Node(FEATURE, size, hidden){
		collideWith(detecting);

		//Set base texture
		setOrigin(8, 8);
	}

	//Activate on collision
	void collide(Node *object) {
		//Send and delete
		send();
		setDelete();
	}
};

class PressureSwitch : public Node, public LogicSender {
private:
	int delay;
	int nextTime = 0;

public:
	//Area constructors
	PressureSwitch(Textures &textures, int delay, CollisionLayer detecting=PLAYER, sf::Vector2i size=sf::Vector2i(12, 12)) : Node(FEATURE, size) {
		this->delay = delay;
		collideWith(detecting);

		//Set base texture
		setTexture(textures.plate);
		setOrigin(8, 8);
	}

	//Activate on collision
	void collide(Node *object, double time) {
		if(nextTime <= time)
			send();

		nextTime = time + delay;
	}

	//Deactivate on update
	void update(double time) {
		setHidden(nextTime > time);
	}
};

class EmptySwitch : public Node, public LogicSender {
private:
	int collisionTime;

public:
	//Area constructors
	EmptySwitch(CollisionLayer detecting=ENEMY, sf::Vector2i size=sf::Vector2i(16, 16)) : Node(FEATURE, size, true){
		collideWith(detecting);
	}

	//Reset on collision
	void collide(Node *object) {
		collisionTime = 0;
	}

	//Wait for multiple updates
	void update(double time) {
		collisionTime++;

		//Send and delete
		if(collisionTime >= 5) {
			send();
			setDelete();
		}

	}
};