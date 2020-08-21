#pragma once
#define PI 3.14159265

/*
 * Created by Stuart Irwin on 4/13/2019.
 * enums for tiles and collision
 */

enum CollisionLayer {
	MAP,
	LOGIC,
	SWITCH,
	FEATURE,
	ENDSCREEN,
	KEY,
	LIGHTING,
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