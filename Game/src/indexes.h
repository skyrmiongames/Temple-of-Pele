#pragma once

#include "engine/GridMaker.h"
#include "enums.h"

static const std::map<char, int> displayIndex = {
	{'#', 0},
	{'@', 0},
	{',', 4},
	{'*', 2},
	{'+', 3},
	{' ', -1},
	{'~', -1},
	{'=', -1}
};

static const std::map<char, int> animatedIndex = {
	{'~', 1},
	{'=', 1},
	{'+', 0},
	{' ', -1}
};

static const std::map<char, int> collisionIndex = {
	{'#', WALL},
	{'+', WALL},
	{'@', WALL},
	{' ', EMPTY},
	{'~', EMPTY},
	{'=', EMPTY}
};