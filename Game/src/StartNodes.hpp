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
		//First door
		Door *door1 = new Door();
		door1->setPosition(256, 112);
		UpdateList::add_node(door1);

		//Auto open door
		AreaSwitch *area1 = new AreaSwitch(false);
		area1->add_channel(door1);
		area1->setPosition(265, 106);
		UpdateList::add_node(area1);

		//Second unloaded door
		NodeLoader *loader1 = new NodeLoader();
		Door *door2 = new Door(true, true);
		loader1->add_node(door2, sf::Vector2f(14, 11));

		//Auto close door
		AreaSwitch *area2 = new AreaSwitch(false);
		area2->add_channel(loader1);
		area2->setPosition(202, 170);
		UpdateList::add_node(area2);
	}
};