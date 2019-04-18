#include "Node.h"

/*
 * Created by Stuart Irwin on 4/17/2019.
 * Base door object
 */

class Doors : public Node {
private:
	//Base door
	const bool vertical;
	const Node paired;

	//Door current state
	int shown;
	int state;
	double nextTime = 0;
	bool placed = false;

public:
	//Build pair of doors
	Door(bool vertical=false, bool closing=false) : Node(SOLID, sf::Vector2i(16, 16)) {
		paired = Node(SOLID, sf::Vector2i(16, 16));

		//Set variables
		this->shown = closing ? 0 : 16;
		this->vertical = vertical;
		this->state = closing ? 1 : 0;

		//Configure door positions
		setOrigin(0, 0);
		paired.setOrigin(16, 16);

		//Rotate door properly
		if(vertical) {
			setRotation(90);
			paired.setRotation(90);
		}
	}

	//Start to open door
	void activate() {
		state = 2;
	}

	//Continue door animation
	void update(double time) {
		if(state == 1) {
			//Closing
			if(shown < 16 && time >= nextTime) {
				nextTime = time += .2;
				shown += 1;
			} else if(shown == 16)
				state = 0;
		} else if(state == 2) {
			//Opening
			if(shown > 0 && time >= nextTime) {
				nextTime = time += .2;
				shown -= 1;
			} else if(shown == 0)
				state = 0;
		}

		if(!placed) {
			//Calculate opposite corner
			sf::Vector2i offset = getPosition() + sf::Vector2i(16, 16);
			if(vertical)
				offset.y += 16;
			else
				offset.x += 16;

			//Confirm second door position
			paired.setPosition(offset);
			placed = true;
		}

		//Set shown amount of texture
		setTextureRect(sf::IntRect (0, 0, shown, 16));
		paired.setTextureRect(sf::IntRect (0, 0, shown, 16));
	}

	//Set doors shared texture
	void set_textures(sf::Texture shared) {
		setTexture(shared);
		paired.setTexture(shared);

		//Set mirroring
		if(vertical)
			paired.scale(1, -1);
		else
			paired.scale(-1, 1);
	}
}