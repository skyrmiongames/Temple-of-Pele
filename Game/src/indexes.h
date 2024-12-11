#pragma once

#include "Skyrmion/tiling/GridMaker.h"
#include "enums.h"

static const std::map<int, int> displayIndex = {
	{'#', 0},
	{'@', 0},
	{',', 4},
	{'*', 2},
	{'+', 3},
	{'%', 3},
	{' ', -1},
	{'~', -1},
	{'=', -1}
};

static const std::map<int, int> animatedIndex = {
	{'~', 1},
	{'=', 1},
	{'+', 0},
	{'%', 0},
	{' ', -1}
};

static const std::map<int, int> collisionIndex = {
	{'=', FULL},
	{'~', FULL},
	{'#', FULL},
	{'@', FULL},
	{'+', FULL},
	{'%', FULL},
	{' ', FULL}
};

static const std::map<int, int> fireballCollisionIndex = {
	{'=', EMPTY},
	{'~', EMPTY},
	{'#', FULL},
	{'@', FULL},
	{'+', FULL},
	{'%', FULL},
	{' ', FULL}
};

static const std::map<int, int> lightIndex = {
	{'=', 70},
	{'~', 70},
	{'+', 100},
	{'>', 100},
	{'#', -100},
	{'@', -100},
	{' ', -100}
};