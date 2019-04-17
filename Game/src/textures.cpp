#pragma once
#include "textures.h"

sf::Texture textures::playerIdleDown;
sf::Texture textures::playerIdleUp;
sf::Texture textures::playerIdleSide;
sf::Texture textures::playerMoveDown;
sf::Texture textures::playerMoveUp;
sf::Texture textures::playerMoveSide;

sf::Texture textures::healthSpriteTexture;

sf::Texture textures::Enemy1Gif;

void textures::load()
{
	playerIdleDown.loadFromFile("resources/Player_IdleDown.png");
	playerIdleUp.loadFromFile("resources/Player_IdleUp.png");
	playerIdleSide.loadFromFile("resources/Player_IdleSide.png");
	playerMoveDown.loadFromFile("resources/Player_WalkDown.png");
	playerMoveUp.loadFromFile("resources/Player_WalkUp.png");
	playerMoveSide.loadFromFile("resources/Player_WalkSide.png");

	healthSpriteTexture.loadFromFile("resources/Health_HeartsGif.png");

	Enemy1Gif.loadFromFile("Enemy1Gif.png");
}