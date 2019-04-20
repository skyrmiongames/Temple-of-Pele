#include "Node.h"
#include "Player.h"
#include "GridMaker.h"

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
		this->state = closing ? -1 : -2;
		this->vertical_shown = locked ? 16 : 0;

		//Configure door properties
		setTexture(textures->doors);

		//Rotate door properly
		if(vertical)
			setRotation(90);
	}

	//Can delete after opening
	UseAmount is_singleton() {
		return SINGLE;
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
		//Finalize door position
		if(state < 0) {
			setPosition(getPosition() - sf::Vector2f(8, 8));
			state += 2;
			GridMaker::set_tile(getPosition(), '#');
		}

		if(state == 1) {
			//Closing animation
			if(horizontal_shown > 0 && time >= nextTime) {
				nextTime = time += 0.05;
				horizontal_shown--;
			} else if(horizontal_shown == 0)
				state = 0;
		} else if(state == 2) {
			//Opening animation
			if(horizontal_shown < 16 && time >= nextTime) {
				nextTime = time += 0.05;
				horizontal_shown++;
			} else if(horizontal_shown == 16) {
				GridMaker::set_tile(getPosition(), '.');
				set_delete();
			}
		}

		//Set shown amount of texture
		setTextureRect(sf::IntRect (horizontal_shown, vertical_shown, horizontal_shown + 16, vertical_shown + 16));
	}
};