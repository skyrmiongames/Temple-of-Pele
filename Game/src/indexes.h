#pragma once

#include "Skyrmion/GridMaker.h"
#include "enums.h"

static const std::map<char, int> displayIndex = {
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

static const std::map<char, int> animatedIndex = {
	{'~', 1},
	{'=', 1},
	{'+', 0},
	{'%', 0},
	{' ', -1}
};

static const std::map<char, int> collisionIndex = {
	{'=', -1},
	{'~', -1},
	{'#', -2},
	{'@', -2},
	{'+', -2},
	{'%', -2},
	{' ', -2}
};

static const std::map<char, int> lightIndex = {
	{'=', 70},
	{'~', 70},
	{'+', 100},
	{'>', 100},
	{'#', -100},
	{'@', -100},
	{'+', -100},
	{' ', -100}
};