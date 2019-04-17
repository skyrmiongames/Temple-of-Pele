#include "Player.h"
#include "textures.h"

Player::Player() :Entity(60, 0, false, 1.2)
{
	this->setTexture(textures::playerIdleDown);
	this->healthSprite.setTexture(textures::healthSpriteTexture);
}

Player::~Player()
{

}

void Player::eightWayMovement()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) // up
	{
		this->setTexture(textures::playerMoveUp);
		move(North);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) // down
	{
		this->setTexture(textures::playerMoveDown);
		move(South);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) // left
	{
		this->setTexture(textures::playerMoveSide);
		move(West);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) // right
	{
		this->setTexture(textures::playerMoveSide);
		move(East);
	}
}

void Player::update()
{
	eightWayMovement();
	healthSprite.setPosition(this->getPosition().x - 12.5, this->getPosition().y - 23);
}