#include "NodeSpawner.h"

/*
 * Created by Stuart Irwin on 4/22/2019.
 * Node spawners on full map startup
 */

class FullSpawner : public NodeSpawner {
private:
	//Lower right room (origin at top corner)
	void codeRoom(NodeLoader *loader, int x, int y) {
		//Left end plate
		PressureSwitch *plate = new PressureSwitch(10);
		loader->add_node(plate, x + 3, y + 2);

		//Left mid plate
		plate = new PressureSwitch(10);
		loader->add_node(plate, x + 5, y + 2);

		//Right mid plate
		plate = new PressureSwitch(10);
		loader->add_node(plate, x + 7, y + 2);

		//Right end plate
		plate = new PressureSwitch(10);
		loader->add_node(plate, x + 9, y + 2);

		//End door
		Door *door = new Door();
		loader->add_node(door, x + 13, y + 1);
	}

	//Central room (origin at center)
	void centerRoom(NodeLoader *loader, int x, int y) {
		//Left bridge set
		Bridge *bridge1 = new Bridge(North);
		Bridge *bridge2 = new Bridge(North);
		bridge1->add_channel(bridge2);
		loader->add_node(bridge1, x - 5, y + 2);
		loader->add_node(bridge2, x - 5, y + 1);

		//Left torch
		AreaSwitch *torch = new AreaSwitch(false, PLAYER, sf::Vector2i(17, 17));
		torch->add_channel(bridge1);
		loader->add_node(torch, x - 3, y + 3);

		//Right bridge set
		bridge1 = new Bridge(North);
		bridge2 = new Bridge(North);
		bridge1->add_channel(bridge2);
		loader->add_node(bridge1, x + 5, y + 2);
		loader->add_node(bridge2, x + 5, y + 1);

		//Right torch
		torch = new AreaSwitch(false, PLAYER, sf::Vector2i(17, 17));
		torch->add_channel(bridge1);
		loader->add_node(torch, x + 3, y + 3);
	}

public:
	void spawn() {
		NodeLoader mainLoader;

		//Load each room
		codeRoom(&mainLoader, 50, 25);
		centerRoom(&mainLoader, 38, 13);

		mainLoader.activate();
	}
};