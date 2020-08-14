#include "NodeLoader.hpp"
#include "Door.hpp"
#include "AreaSwitch.h"
#include "Key.hpp"
#include "Bridge.hpp"
#include "EndScreen.hpp"
#include "Enemy.h"
#include "EnemyFireball.h"
#include "LogicCode.hpp"
#include "LogicGates.hpp"
#include "FireLauncher.hpp"

/*
 * Created by Stuart Irwin on 4/22/2019.
 * Node spawners on full map startup
 */

//Lower left room (origin at top)
void trapRoom(Textures &textures, NodeLoader *loader, int x, int y) {
	//Trap specific loader
	NodeLoader *loader1 = new NodeLoader();

	//Trap activator
	AreaSwitch *area = new AreaSwitch();
	area->addChannel(loader1);
	loader->add_node(area, x + 4, y + 2);
	area->setPosition(area->getPosition() + sf::Vector2f(-8, 0));

	//Already closed door
	Door *door1 = new Door(textures, false, true);
	loader->add_node(door1, x - 1, y + 2);

	//Dramatic closing door
	Door *door2 = new Door(textures, true, true);
	loader1->add_node(door2, x + 5, y + 2);

	//Enemy 1
	Enemy* enemy = new Enemy();
	loader1->add_node(enemy, x, y + 1);

	//Enemy 2
	enemy = new Enemy();
	loader1->add_node(enemy, x + 2, y + 3);

	//Trap finished detector
	EmptySwitch *empty = new EmptySwitch(ENEMY, sf::Vector2i(80, 80));
	empty->addChannel(door1);
	empty->addChannel(door2);
	loader1->add_node(empty, x + 2, y + 2);

	//Basic key
	Key *key = new Key(textures);
	loader->add_node(key, x - 3, y + 2);
}

//Lower right room (origin at top)
void codeRoom(Textures &textures, NodeLoader *loader, int x, int y) {
	//Code checker
	LogicCode *code = new LogicCode();
	LogicCounter *counter = new LogicCounter(4);

	//Reset lock
	LockableGate *lock = new LockableGate();
	code->addChannel(new LockableGatePassthrough(lock));

	//Reset timer
	LogicTimer *timer = new LogicTimer(LOGIC, 0.5);
	timer->addChannel(lock);
	counter->addChannel(timer);
	loader->add_node(timer, x, y);

	//Left end plate
	PressureSwitch *plate = new PressureSwitch(textures);
	plate->addChannel(code->get_key());
	plate->addChannel(counter);
	lock->addChannel(plate);
	loader->add_node(plate, x + 3, y + 2);

	//Right end plate
	plate = new PressureSwitch(textures);
	plate->addChannel(code->get_key());
	plate->addChannel(counter);
	lock->addChannel(plate);
	loader->add_node(plate, x + 9, y + 2);

	//Left mid plate
	plate = new PressureSwitch(textures);
	plate->addChannel(code->get_key());
	plate->addChannel(counter);
	lock->addChannel(plate);
	loader->add_node(plate, x + 5, y + 2);

	//Right mid plate
	plate = new PressureSwitch(textures);
	plate->addChannel(code->get_key());
	plate->addChannel(counter);
	lock->addChannel(plate);
	loader->add_node(plate, x + 7, y + 2);

	//End door
	Door *door = new Door(textures, false, true);
	code->addChannel(door);
	loader->add_node(door, x + 13, y + 1);
}

//Central room (origin at center)
void centerRoom(Textures &textures, NodeLoader *loader, int x, int y) {
	//Left bridge set
	Bridge *bridge1 = new Bridge(textures, North);
	Bridge *bridge2 = new Bridge(textures, North);
	bridge1->addChannel(bridge2);
	loader->add_node(bridge1, x - 5, y + 2);
	loader->add_node(bridge2, x - 5, y + 1);

	//Left torch
	AreaSwitch *torch = new AreaSwitch(false, FIREBALL, sf::Vector2i(17, 17));
	torch->setTexture(textures.brazier);
	torch->addChannel(bridge1);
	loader->add_node(torch, x - 3, y + 3);

	//Right bridge set
	bridge1 = new Bridge(textures, North);
	bridge2 = new Bridge(textures, North);
	bridge1->addChannel(bridge2);
	loader->add_node(bridge1, x + 5, y + 2);
	loader->add_node(bridge2, x + 5, y + 1);

	//Right torch
	torch = new AreaSwitch(false, FIREBALL, sf::Vector2i(17, 17));
	torch->setTexture(textures.brazier);
	torch->addChannel(bridge1);
	loader->add_node(torch, x + 3, y + 3);

	//Fireball enemy
	Enemy *enemy = new FireEnemy();
	loader->add_node(enemy, x, y + 1);

	//Center key
	Key *key = new Key(textures);
	loader->add_node(key, x, y - 1);

	//Upper bridge set
	bridge1 = new Bridge(textures, South);
	bridge2 = new Bridge(textures, South);
	bridge1->addChannel(bridge2);
	loader->add_node(bridge1, x, y - 3);
	loader->add_node(bridge2, x, y - 2);

	//Upper pressure plate
	AreaSwitch *plate = new AreaSwitch(false);
	plate->setTexture(textures.plate);
	plate->addChannel(bridge1);
	loader->add_node(plate, x, y - 4);

	//Far right door
	Door *door = new Door(textures, false, true, true);
	loader->add_node(door, x + 9, y);
}

//Central left room (origin at top)
void revealRoom(Textures &textures, NodeLoader *loader, int x, int y) {
	//Fire trap 1
	FireLauncher *launcher1 = new FireLauncher(textures, South);
	loader->add_node(launcher1, x + 1, y);

	//Fire trap 2
	FireLauncher *launcher2 = new FireLauncher(textures, South);
	loader->add_node(launcher2, x + 3, y);

	//Fire trap 3
	FireLauncher *launcher3 = new FireLauncher(textures, South);
	loader->add_node(launcher3, x + 5, y);

	//Fire trap 4
	FireLauncher *launcher4 = new FireLauncher(textures, South);
	loader->add_node(launcher4, x + 7, y);

	//Pressure plate
	PressureSwitch *plate = new PressureSwitch(textures);
	plate->addChannel(launcher1);
	loader->add_node(plate, x + 9, y + 2);

	//Timer 1
	LogicTimer *timer1 = new LogicTimer(LOGIC, 0.7);
	timer1->addChannel(launcher4);
	plate->addChannel(timer1);
	loader->add_node(timer1, x, y);

	//Timer 2
	LogicTimer *timer2 = new LogicTimer(LOGIC, 0.7);
	timer2->addChannel(launcher2);
	timer1->addChannel(timer2);
	loader->add_node(timer2, x, y);

	//Timer 3
	LogicTimer *timer3 = new LogicTimer(LOGIC, 0.7);
	timer3->addChannel(launcher3);
	timer2->addChannel(timer3);
	loader->add_node(timer3, x, y);

	//Timer 4
	LogicTimer *timer4 = new LogicTimer(LOGIC, 0.7);
	timer4->addChannel(plate);
	timer3->addChannel(timer4);
	loader->add_node(timer4, x, y);

	//Torch 1
	AreaSwitch *torch = new AreaSwitch(false, FIREBALL, sf::Vector2i(17, 17));
	torch->setTexture(textures.brazier);
	loader->add_node(torch, x + 1, y + 3);

	//Torch 2
	torch = new AreaSwitch(false, FIREBALL, sf::Vector2i(17, 17));
	torch->setTexture(textures.brazier);
	loader->add_node(torch, x + 3, y + 3);

	//Torch 3
	torch = new AreaSwitch(false, FIREBALL, sf::Vector2i(17, 17));
	torch->setTexture(textures.brazier);
	loader->add_node(torch, x + 5, y + 3);

	//Torch 4
	torch = new AreaSwitch(false, FIREBALL, sf::Vector2i(17, 17));
	torch->setTexture(textures.brazier);
	loader->add_node(torch, x + 7, y + 3);
}

//Central right room (origin at top)
void bridgeRoom(Textures &textures, NodeLoader *loader, int x, int y) {
	//Enemy 1
	Enemy* enemy = new Enemy();
	loader->add_node(enemy, x + 2, y + 2);

	//Enemy 2
	enemy = new FireEnemy();
	loader->add_node(enemy, x + 3, y + 4);

	//Enemy 3
	enemy = new Enemy();
	loader->add_node(enemy, x + 2, y + 6);

	//Bridge set
	Bridge *bridge1 = new Bridge(textures, North);
	Bridge *bridge2 = new Bridge(textures, North);
	bridge1->addChannel(bridge2);
	loader->add_node(bridge1, x + 13, y + 5);
	loader->add_node(bridge2, x + 13, y + 4);

	//Bridge pressure plate
	AreaSwitch *plate = new AreaSwitch(false);
	plate->setTexture(textures.plate);
	plate->addChannel(bridge1);
	loader->add_node(plate, x + 7, y + 6);

	//Enemy 4
	enemy = new Enemy();
	loader->add_node(enemy, x + 13, y + 2);
}

//Upper center trap room (origin at top)
void bossRoom(Textures &textures, NodeLoader *loader, int x, int y) {
	//Trap specific loader
	NodeLoader *loader1 = new NodeLoader();

	//Trap activator
	AreaSwitch *area = new AreaSwitch();
	area->addChannel(loader1);
	loader->add_node(area, x + 8, y + 4);
	area->setPosition(area->getPosition() + sf::Vector2f(-8, 0));

	//Already closed door
	Door *door1 = new Door(textures, false, true);
	loader->add_node(door1, x - 1, y + 1);

	//Dramatic closing door
	Door *door2 = new Door(textures, true, true);
	loader1->add_node(door2, x + 9, y + 4);

	//Enemy 1
	Enemy* enemy = new Enemy();
	loader1->add_node(enemy, x + 2, y + 1);

	//Enemy 2
	enemy = new Enemy();
	loader1->add_node(enemy, x + 5, y + 3);

	//Enemy 3
	enemy = new FireEnemy();
	loader1->add_node(enemy, x + 3, y + 3);

	//Trap finished detector
	EmptySwitch *empty = new EmptySwitch(ENEMY, sf::Vector2i(160, 80));
	empty->addChannel(door1);
	empty->addChannel(door2);
	loader1->add_node(empty, x + 4, y + 2);
}

//Top right room (origin at bottom)
void endRoom(Textures &textures, NodeLoader *loader, int x, int y) {
	//Fire trap 1
	FireLauncher *launcher = new FireLauncher(textures, East, 2);
	loader->add_node(launcher, x, y);

	//Fire trap 2
	launcher = new FireLauncher(textures, East, 2);
	loader->add_node(launcher, x, y - 1);

	//Fire trap 3
	launcher = new FireLauncher(textures, East, 2);
	loader->add_node(launcher, x, y - 2);

	//Fire trap 4
	launcher = new FireLauncher(textures, East, 2);
	loader->add_node(launcher, x, y - 3);

	//Return bridge set
	Bridge *bridge1 = new Bridge(textures, South);
	Bridge *bridge2 = new Bridge(textures, South);
	Bridge *bridge3 = new Bridge(textures, South);
	bridge1->addChannel(bridge2);
	bridge2->addChannel(bridge3);
	loader->add_node(bridge1, x + 1, y - 3);
	loader->add_node(bridge2, x + 1, y - 2);
	loader->add_node(bridge3, x + 1, y - 1);

	//Bridge pressure plate
	AreaSwitch *plate = new AreaSwitch(false);
	plate->setTexture(textures.plate);
	plate->addChannel(bridge1);
	loader->add_node(plate, x, y - 4);

	//Locked door
	Door *door = new Door(textures, false, false, true);
	loader->add_node(door, x, y - 6);

	//Game exit
	EndScreen *end = new EndScreen(textures, true);
	loader->add_node(end, x + 8, y - 7);
}

void spawn(Textures &textures) {
	NodeLoader mainLoader;

	//Front door
	Door *door = new Door(textures, true);
	mainLoader.add_node(door, 29, 32);

	//Load each room
	codeRoom(textures, &mainLoader, 41, 25);
	trapRoom(textures, &mainLoader, 10, 24);
	centerRoom(textures, &mainLoader, 29, 13);
	revealRoom(textures, &mainLoader, 2, 11);
	bridgeRoom(textures, &mainLoader, 48, 11);
	bossRoom(textures, &mainLoader, 39, 3);
	endRoom(textures, &mainLoader, 61, 9);

	mainLoader.activate();
}