#pragma once
#include "Node.h"

class textures
{
  public:
	  static void load()
	  {
		  playerIdleDown.loadFromFile("resources/Player_IdleDown.png");
		  playerIdleUp.loadFromFile("resources/Player_IdleUp.png");
		  playerIdleSide.loadFromFile("resources/Player_IdleSide.png");
		  playerMoveDown.loadFromFile("resources/Player_WalkDown.png");
		  playerMoveUp.loadFromFile("resources/Player_WalkUp.png");
		  playerMoveSide.loadFromFile("resources/Player_WalkSide.png");

		  healthSpriteTexture.loadFromFile("resources/Health_HeartsGif.png");
	  };

	static sf::Texture playerIdleDown;
	static sf::Texture playerIdleUp;
	static sf::Texture playerIdleSide;
	static sf::Texture playerMoveDown;
	static sf::Texture playerMoveUp;
	static sf::Texture playerMoveSide;

	static sf::Texture healthSpriteTexture;
};