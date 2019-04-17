#pragma once
#include "Node.h"

class textures
{
public:
	static sf::Texture playerIdleDown;
	static sf::Texture playerIdleUp;
	static sf::Texture playerIdleSide;
	static sf::Texture playerMoveDown;
	static sf::Texture playerMoveUp;
	static sf::Texture playerMoveSide;

	static sf::Texture healthSpriteTexture;

	static sf::Texture Enemy1Gif;

	static void load();
};