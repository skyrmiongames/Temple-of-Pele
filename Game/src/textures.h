#pragma once
#include "Node.h"

class Textures
{
public:
	//Player animations
	sf::Texture playerIdleDown;
	sf::Texture playerIdleUp;
	sf::Texture playerIdleRight;
	sf::Texture playerIdleLeft;
	sf::Texture playerMoveDown;
	sf::Texture playerMoveUp;
	sf::Texture playerMoveRight;
	sf::Texture playerMoveLeft;

	//Player items
	sf::Texture healthSpriteTexture;
	sf::Texture knife;
	sf::Texture key;

	//Enemies
	sf::Texture Enemy1Gif;

	//Tile objects
	sf::Texture doors;
	sf::Texture exitLight;
	sf::Texture plate;
	sf::Texture bridge;

	Textures()
	{
		//Player animations
		playerIdleDown.loadFromFile("resources/player/Player_IdleDown.png");
		playerIdleUp.loadFromFile("resources/player/Player_IdleUp.png");
		playerIdleRight.loadFromFile("resources/player/Player_IdleRight.png");
		playerIdleLeft.loadFromFile("resources/player/Player_IdleLeft.png");
		playerMoveDown.loadFromFile("resources/player/Player_WalkDown.png");
		playerMoveUp.loadFromFile("resources/player/Player_WalkUp.png");
		playerMoveRight.loadFromFile("resources/player/Player_WalkRight.png");
		playerMoveLeft.loadFromFile("resources/player/Player_WalkLeft.png");

		//Player items
		healthSpriteTexture.loadFromFile("resources/player/Health_HeartsGif.png");
		knife.loadFromFile("resources/player/Knife_Base.png");
		key.loadFromFile("resources/Key_Tile.png");

		//Enemies
		Enemy1Gif.loadFromFile("resources/Enemy1_BaseGif.png");

		//Tile objects
		doors.loadFromFile("resources/tiles/Doors.png");
		exitLight.loadFromFile("resources/tiles/Exit_Light.png");
		plate.loadFromFile("resources/tiles/Pressure_Plate.png");
		bridge.loadFromFile("resources/tiles/Bridge.png");
	}
};