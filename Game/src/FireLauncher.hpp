#include "Fireball.h"
#include "engine/UpdateList.h"

/*
 * Created by Stuart Irwin on 4/23/2019.
 * Launch fireball in specific direction
 */

class FireLauncher : public Node, public LogicReciever {
private:
	double angle = PI/2;
	int delay = 0;
	int nextTime = 0;

public:
	//Fireball launcher
	FireLauncher(Textures &textures, OrthagonalDirection direction, int delay=0) : Node(FEATURE, sf::Vector2i(16, 16)) {
		//Configure tile properties
		setTexture(textures.spitter);
		this->delay = delay;

		//Rotate door properly
		switch(direction) {
			case East:
				setRotation(90);
				angle = 0;
				break;
			case South:
				setRotation(180);
				angle = 3*PI/2;
				break;
			case West:
				setRotation(-90);
				angle = PI;
				break;
			default:
				break;
		}
	}

	void update(double time) {
		if(delay > 0 && time >= nextTime) {
			activate();
			nextTime = time + delay;
		}
	}

	//Launch fireball in direction
	void activate() {
		Fireball *launched = new Fireball(getPosition(), angle);
		UpdateList::addNode(launched);
	}
};