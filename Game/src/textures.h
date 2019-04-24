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
	sf::Texture EnemyLeftGif;
	sf::Texture EnemyRightGif;
	sf::Texture FireEnemyLeftGif;
	sf::Texture FireEnemyRightGif;
	sf::Texture Fireball;

	//Tile objects
	sf::Texture doors;
	sf::Texture exitLight;
	sf::Texture plate;
	sf::Texture bridge;
	sf::Texture spitter;
	sf::Texture brazier;

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
		EnemyRightGif.loadFromFile("resources/EnemyRight_BaseGif.png");
		EnemyLeftGif.loadFromFile("resources/EnemyLeft_BaseGif.png");
		FireEnemyRightGif.loadFromFile("resources/FireEnemyRight_BaseGif.png");
		FireEnemyLeftGif.loadFromFile("resources/FireEnemyLeft_BaseGif.png");
		Fireball.loadFromFile("resources/FireBall_BaseGif.png");

		//Tile objects
		doors.loadFromFile("resources/tiles/Doors.png");
		exitLight.loadFromFile("resources/tiles/Exit_Light.png");
		plate.loadFromFile("resources/tiles/Pressure_Plate.png");
		bridge.loadFromFile("resources/tiles/Bridge.png");
		spitter.loadFromFile("resources/tiles/Spitter.png");
		brazier.loadFromFile("resources/tiles/Brazier_base.png");
	}
};