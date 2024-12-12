#pragma once

#include "Skyrmion/tiling/GridMaker.h"
#include "enums.h"

static const std::map<int, int> displayIndex = {
	{'#', -1},
	{'@', -1},
	{'_', -1},
	{',', 4},
	{'v', 4},
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

static const std::map<int, int> quadPreprocessIndex = {
	{'#', '#'},
	{'@', '#'},
	{',', ','},
	{'.', '.'},
	{'_', '.'},
	{'=', '.'},
	{'[', '.'},
	{']', '.'},
	{'{', '.'},
	{'v', '~'},
	{'+', '~'},
	{'%', '~'},
	{'*', '~'},
	{'~', '~'},
	{' ', -1}
};

static const std::vector<std::array<int,5>> quadIndex = genQuadRotations({
	{'#', '#', '#', '#', 0},
	{'.', '.', '.', '.', 1},
	{',', ',', ',', ',', 4},
	{'#', '#', '#', '.', 6},
	{'#', '#', '.', '.', 7},
	{'#', '.', '.', '.', 8},
	{'.', '.', '.', ',', 9},
	{'.', '.', ',', ',', 10},
	{'.', ',', ',', ',', 11},
	{'#', '#', '#', '~', 12},
	{'#', '#', '~', '~', 13},
	{'#', '~', '~', '~', 14},
	{'#', '~', '.', '.', 15},
	{'~', '~', '#', '.', 16},
	{'#', '~', '#', '.', 17},
}, 18);