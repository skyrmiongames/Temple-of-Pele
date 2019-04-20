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

	sf::Texture knife;
	sf::Texture key;

	sf::Texture doors;

	Textures()
	{
		playerIdleDown.loadFromFile("resources/player/Player_IdleDown.png");
		playerIdleUp.loadFromFile("resources/player/Player_IdleUp.png");
		playerIdleRight.loadFromFile("resources/player/Player_IdleRight.png");
		playerIdleLeft.loadFromFile("resources/player/Player_IdleLeft.png");
		playerMoveDown.loadFromFile("resources/player/Player_WalkDown.png");
		playerMoveUp.loadFromFile("resources/player/Player_WalkUp.png");
		playerMoveRight.loadFromFile("resources/player/Player_WalkRight.png");
		playerMoveLeft.loadFromFile("resources/player/Player_WalkLeft.png");

		healthSpriteTexture.loadFromFile("resources/player/Health_HeartsGif.png");

		Enemy1Gif.loadFromFile("resources/Enemy1_BaseGif.png");

		knife.loadFromFile("resources/player/Knife_Base.png");
		key.loadFromFile("resources/Key_Tile.png");

		doors.loadFromFile("resources/Doors.png");
	}
};