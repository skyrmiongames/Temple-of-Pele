#include "textures.h"

textures::textures()
{
	playerIdleDown.loadFromFile("resources/Player_IdleDown.png");
	playerIdleUp.loadFromFile("resources/Player_IdleUp.png");
	playerIdleSide.loadFromFile("resources/Player_IdleSide.png");
	playerMoveDown.loadFromFile("resources/Player_WalkDown.png");
	playerMoveUp.loadFromFile("resources/Player_WalkUp.png");
	playerMoveSide.loadFromFile("resources/Player_WalkSide.png");
}

textures::~textures()
{

};