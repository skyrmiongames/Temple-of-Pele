#pragma once
#include "Node.h"

class Textures
{
public:
	sf::Texture playerIdleDown;
	sf::Texture playerIdleUp;
	sf::Texture playerIdleSide;
	sf::Texture playerMoveDown;
	sf::Texture playerMoveUp;
	sf::Texture playerMoveSide;

	sf::Texture healthSpriteTexture;

	sf::Texture Enemy1Gif;

	Textures()
	{
		playerIdleDown.loadFromFile("resources/Player_IdleDown.png");
		playerIdleUp.loadFromFile("resources/Player_IdleUp.png");
		playerIdleSide.loadFromFile("resources/Player_IdleSide.png");
		playerMoveDown.loadFromFile("resources/Player_WalkDown.png");
		playerMoveUp.loadFromFile("resources/Player_WalkUp.png");
		playerMoveSide.loadFromFile("resources/Player_WalkSide.png");

		healthSpriteTexture.loadFromFile("resources/Health_HeartsGif.png");
	}
};