#pragma once
#define PI 3.14159265

/*
 * Created by Stuart Irwin on 4/13/2019.
 * enums for tiles and collision
 */

enum TileType {
	AIR,
	LAVA,
	SOLID
};

enum CollisionLayer {
	MAP,
	LOGIC,
	SWITCH,
	FEATURE,
	KEY,
	GUI,
	ENEMY,
	SWORD,
	FIREBALL,
	ENDSCREEN,
	DEATH,
	PLAYER,
	LIGHTING
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