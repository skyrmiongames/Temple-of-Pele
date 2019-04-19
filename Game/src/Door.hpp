#include "Node.h"
#include "Player.h"

/*
 * Created by Stuart Irwin on 4/17/2019.
 * Base door object
 */

class Door : public Node {
private:
	//Door base state
	int vertical_shown;

	//Door current state
	int horizontal_shown;
	int state;
	double nextTime = 0;

public:
	//Build door
	Door(bool closing=false, bool vertical=false, bool locked=false) : Node(SOLID, sf::Vector2i(16, 16)) {
		//Set variables
		this->horizontal_shown = closing ? 16 : 0;
		this->state = closing ? 1 : 0;
		this->vertical_shown = locked ? 16 : 0;

		//Configure door properties
		setOrigin(0, 0);
		setTexture(textures->doors);

		//Rotate door properly
		if(vertical) {
			setOrigin(16, 0);
			setRotation(90);
		}
	}

	//Can delete after opening
	bool is_singleton() {
		return false;
	}

	//Start to open normal door
	void activate() {
		if(vertical_shown == 0)
			state = 2;
	}

	//Start to open locked door
	void collide(Node *object) {
		if(vertical_shown == 16 && object->get_layer() == PLAYER) {
			Player *player = (Player *) object;
			if(player->getKey())
				state = 2;
		}
	}

	//Continue door animation
	void update(double time) {
		if(state == 1) {
			//Closing
			if(horizontal_shown > 0 && time >= nextTime) {
				nextTime = time += 0.05;
				horizontal_shown--;
			} else if(horizontal_shown == 0)
				state = 0;
		} else if(state == 2) {
			//Opening
			if(horizontal_shown < 16 && time >= nextTime) {
				nextTime = time += 0.05;
				horizontal_shown++;
			} else if(horizontal_shown == 16)
				set_delete();
		}

		//Set shown amount of texture
		setTextureRect(sf::IntRect (horizontal_shown, vertical_shown, horizontal_shown + 16, vertical_shown + 16));
	}
};