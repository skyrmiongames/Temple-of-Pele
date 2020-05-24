#pragma once
#define PI 3.14159265

/*
 * Created by Stuart Irwin on 4/13/2019.
 * enums for tiles and collision
 */

enum CollisionLayer {
	MAP,
	LOGIC,
	TORCH,
	SWITCH,
	ENDSCREEN,
	KEY,
	GUI,
	ENEMY,
	SWORD,
	PLAYER,
	FIREBALL,
};

enum OrthagonalDirection {
	North,
	Northeast,
	East,
	Southeast,
	South,
	Southwest,
	West,
	Northwest
};

enum UseAmount {
	MULTI,
	SINGLE,
	DELETE
};