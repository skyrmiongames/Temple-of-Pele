#include "Node.h"
#include "GridMaker.h"
#include "enums.h"

/*
 * Created by Stuart Irwin on 4/20/2019.
 * Activatable bridge to go over lava
 */

class Bridge : public Node {
private:
	//Bridge current state
	int vertical_shown = 0;
	double nextTime = 0;

public:
	//Build bridge
	Bridge(OrthagonalDirection direction) : Node(SWITCH, sf::Vector2i(16, 16)) {
		//Configure bridge properties
		setTexture(textures->bridge);

		//Rotate door properly
		switch(direction) {
			case East:
				setRotation(90);
				setOrigin(0, 16);
				break;
			case South:
				setRotation(180);
				setOrigin(16, 16);
				break;
			case West:
				setRotation(-90);
				setOrigin(16, 0);
				break;
			default:
				break;
		}
	}

	//Continue door animation
	void update(double time) {
		if(vertical_shown < 16) {
			//Closing animation
			if(time >= nextTime) {
				nextTime = time += 0.1;
				vertical_shown++;
			}

			//Set solid ground
			if(vertical_shown == 16)
				GridMaker::set_tile(getPosition(), '.');
		}

		//Set shown amount of texture
		setTextureRect(sf::IntRect(0, vertical_shown, 16, vertical_shown + 16));
	}
};