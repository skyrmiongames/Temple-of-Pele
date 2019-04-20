#pragma once
#define PI 3.14159265

/*
 * Created by Stuart Irwin on 4/13/2019.
 * enums for tiles and collision
 */

enum CollisionLayer {
	SOLID,
	PLAYER,
	SWORD,
	ENEMY,
	FIREBALL,
	KEY,
	TORCH,
	SWITCH
};

enum TileType {
	WALL,
	GROUND,
	EMPTY
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