#include "../Skyrmion/UpdateList.h"
#include "../Fireball.h"

/*
 * Created by Stuart Irwin on 4/23/2019.
 * Launch fireball in specific direction
 */

class FireLauncher : public Node, public LogicReciever {
private:
	sf::Vector2f dir = sf::Vector2f(0, -1);
	int delay;
	double nextTime = 0;

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
				dir = sf::Vector2f(1, 0);
				break;
			case South:
				setRotation(180);
				dir = sf::Vector2f(0, 1);
				break;
			case West:
				setRotation(-90);
				dir = sf::Vector2f(-1, 0);
				break;
			default:
				break;
		}
	}

	void update(double time) {
		if(delay > 1 && (nextTime -= time) <= 0) {
			activate();
			nextTime = delay;
		}
	}

	//Launch fireball in direction
	void activate() {
		Fireball *launched = new Fireball(getPosition(), dir);
		UpdateList::addNode(launched);
	}
};