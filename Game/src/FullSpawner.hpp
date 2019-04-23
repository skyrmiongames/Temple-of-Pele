#include "NodeSpawner.h"

/*
 * Created by Stuart Irwin on 4/22/2019.
 * Node spawners on full map startup
 */

class FullSpawner : public NodeSpawner {
private:
	//Lower left room (origin at top)
	void trapRoom(NodeLoader *loader, int x, int y) {
		//Trap specific loader
		NodeLoader *loader1 = new NodeLoader();

		//Trap activator
		AreaSwitch *area = new AreaSwitch();
		area->add_channel(loader1);
		loader->add_node(area, x + 4, y + 2);
		area->setPosition(area->getPosition() + sf::Vector2f(-8, 0));

		//Already closed door
		Door *door1 = new Door(false, true);
		loader->add_node(door1, x - 1, y + 2);

		//Dramatic closing door
		Door *door2 = new Door(true, true);
		loader1->add_node(door2, x + 5, y + 2);

		//Enemy 1
		Enemy* enemy = new Enemy();
		loader1->add_node(enemy, x, y + 1);

		//Enemy 2
		enemy = new Enemy();
		loader1->add_node(enemy, x + 2, y + 3);

		//Trap finished detector
		EmptySwitch *empty = new EmptySwitch(ENEMY, sf::Vector2i(80, 80));
		empty->add_channel(door1);
		empty->add_channel(door2);
		loader1->add_node(empty, x + 2, y + 2);

		//Basic key
		Key *key = new Key();
		loader->add_node(key, x - 3, y + 2);
	}

	//Lower right room (origin at top)
	void codeRoom(NodeLoader *loader, int x, int y) {
		//Code checker
		LogicCode *code = new LogicCode();

		//Left end plate
		PressureSwitch *plate = new PressureSwitch(4);
		plate->add_channel(code->get_key());
		loader->add_node(plate, x + 3, y + 2);

		//Right end plate
		plate = new PressureSwitch(4);
		plate->add_channel(code->get_key());
		loader->add_node(plate, x + 9, y + 2);

		//Left mid plate
		plate = new PressureSwitch(4);
		plate->add_channel(code->get_key());
		loader->add_node(plate, x + 5, y + 2);

		//Right mid plate
		plate = new PressureSwitch(4);
		plate->add_channel(code->get_key());
		loader->add_node(plate, x + 7, y + 2);

		//End door
		Door *door = new Door(false, true);
		code->add_channel(door);
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

		//Center key
		Key *key = new Key();
		loader->add_node(key, x, y - 1);

		//Upper bridge set
		bridge1 = new Bridge(South);
		bridge2 = new Bridge(South);
		bridge1->add_channel(bridge2);
		loader->add_node(bridge1, x, y - 3);
		loader->add_node(bridge2, x, y - 2);

		//Upper pressure plate
		AreaSwitch *plate = new AreaSwitch(false);
		plate->add_channel(bridge1);
		loader->add_node(plate, x, y - 4);

		//Far right door
		Door *door = new Door(false, true, true);
		loader->add_node(door, x + 9, y);
	}

	//Central right room (origin at top)
	void bridgeRoom(NodeLoader *loader, int x, int y) {
		//Enemy 1
		Enemy* enemy = new Enemy();
		loader->add_node(enemy, x + 2, y + 2);

		//Bridge set
		Bridge *bridge1 = new Bridge(North);
		Bridge *bridge2 = new Bridge(North);
		bridge1->add_channel(bridge2);
		loader->add_node(bridge1, x + 13, y + 5);
		loader->add_node(bridge2, x + 13, y + 4);

		//Bridge pressure plate
		AreaSwitch *plate = new AreaSwitch(false);
		plate->add_channel(bridge1);
		loader->add_node(plate, x + 7, y + 6);

		//Enemy 4
		enemy = new Enemy();
		loader->add_node(enemy, x + 13, y + 2);
	}

	//Upper center trap room (origin at top)
	void bossRoom(NodeLoader *loader, int x, int y) {
		//Trap specific loader
		NodeLoader *loader1 = new NodeLoader();

		//Trap activator
		AreaSwitch *area = new AreaSwitch();
		area->add_channel(loader1);
		loader->add_node(area, x + 4, y + 2);
		area->setPosition(area->getPosition() + sf::Vector2f(-8, 0));

		//Already closed door
		Door *door1 = new Door(false, true);
		loader->add_node(door1, x - 1, y + 2);

		//Dramatic closing door
		Door *door2 = new Door(true, true);
		loader1->add_node(door2, x + 5, y + 2);

		//Enemy 1
		Enemy* enemy = new Enemy();
		loader1->add_node(enemy, x, y + 1);

		//Enemy 2
		enemy = new Enemy();
		loader1->add_node(enemy, x + 2, y + 3);

		//Trap finished detector
		EmptySwitch *empty = new EmptySwitch(ENEMY, sf::Vector2i(80, 80));
		empty->add_channel(door1);
		empty->add_channel(door2);
		loader1->add_node(empty, x + 2, y + 2);

		//Basic key
		Key *key = new Key();
		loader->add_node(key, x - 3, y + 2);
	}

	//Top right room (origin at bottom)
	void endRoom(NodeLoader *loader, int x, int y) {
		//Return bridge set
		Bridge *bridge1 = new Bridge(South);
		Bridge *bridge2 = new Bridge(South);
		Bridge *bridge3 = new Bridge(South);
		bridge1->add_channel(bridge2);
		bridge2->add_channel(bridge3);
		loader->add_node(bridge1, x + 1, y - 3);
		loader->add_node(bridge2, x + 1, y - 2);
		loader->add_node(bridge3, x + 1, y - 1);

		//Bridge pressure plate
		AreaSwitch *plate = new AreaSwitch(false);
		plate->add_channel(bridge1);
		loader->add_node(plate, x, y - 4);

		//Locked door
		Door *door = new Door(false, false, true);
		loader->add_node(door, x, y - 6);

		//Game exit
		EndScreen *end = new EndScreen(true);
		loader->add_node(end, x + 8, y - 7);
	}

public:
	void spawn() {
		NodeLoader mainLoader;

		//Front door
		Door *door = new Door(true);
		mainLoader.add_node(door, 38, 32);

		//Load each room
		codeRoom(&mainLoader, 50, 25);
		trapRoom(&mainLoader, 19, 24);
		centerRoom(&mainLoader, 38, 13);
		bridgeRoom(&mainLoader, 57, 11);
		endRoom(&mainLoader, 70, 9);

		mainLoader.activate();
	}
};