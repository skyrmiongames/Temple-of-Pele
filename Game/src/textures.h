#pragma once
#include "Node.h"

class Textures
{
public:
	sf::Texture playerIdleDown;
	sf::Texture playerIdleUp;
	sf::Texture playerIdleRight;
	sf::Texture playerIdleLeft;
	sf::Texture playerMoveDown;
	sf::Texture playerMoveUp;
	sf::Texture playerMoveRight;
	sf::Texture playerMoveLeft;

	sf::Texture healthSpriteTexture;

	sf::Texture Enemy1Gif;

	sf::Texture Knife;

	Textures()
	{
		playerIdleDown.loadFromFile("resources/Player_IdleDown.png");
		playerIdleUp.loadFromFile("resources/Player_IdleUp.png");
		playerIdleRight.loadFromFile("resources/Player_IdleRight.png");
		playerIdleLeft.loadFromFile("resources/Player_IdleLeft.png");
		playerMoveDown.loadFromFile("resources/Player_WalkDown.png");
		playerMoveUp.loadFromFile("resources/Player_WalkUp.png");
		playerMoveRight.loadFromFile("resources/Player_WalkRight.png");
		playerMoveLeft.loadFromFile("resources/Player_WalkLeft.png");

		healthSpriteTexture.loadFromFile("resources/Health_HeartsGif.png");

		Enemy1Gif.loadFromFile("resources/Enemy1_BaseGif.png");

		Knife.loadFromFile("resources/Knife_Base.png");
	}
};