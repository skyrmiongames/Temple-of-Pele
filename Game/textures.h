#pragma once
#include "src\Node.h"

class textures
{
public:
	textures();
	~textures();

	sf::Texture playerIdleDown;
	sf::Texture playerIdleUp;
	sf::Texture playerIdleSide;
	sf::Texture playerMoveDown;
	sf::Texture playerMoveUp;
	sf::Texture playerMoveSide;
};