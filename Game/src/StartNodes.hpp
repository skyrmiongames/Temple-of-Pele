#include "UpdateList.h"
#include "Door.hpp"
#include "AreaSwitch.h"
#include "NodeLoader.hpp"

/*
 * Created by Stuart Irwin on 4/18/2019.
 * Node spawners on startup
 */

class StartNodes {
public:
	static void test_nodes() {
		//Main loader
		NodeLoader mainLoader;

		//First door
		Door *door = new Door();
		mainLoader.add_node(door, 17, 7);

		//Auto open door
		AreaSwitch *area = new AreaSwitch();
		area->add_channel(door);
		mainLoader.add_node(area, 17, 6);

		//Second unloaded door
		NodeLoader *loader1 = new NodeLoader();
		door = new Door(true, true);
		loader1->add_node(door, 14, 11);

		//Auto close door
		area = new AreaSwitch(PLAYER);
		area->add_channel(loader1);
		mainLoader.add_node(area, 13, 11);

		//Place nodes
		mainLoader.activate();
	}
};