#include "Player.h"
#include "textures.h"

Player::Player() :Entity(60, 0, false, 1.2)
{
	this->setTexture(textures::playerIdleDown);
	//sf::IntRect playerRectangle(0,0 10, 16);
	this->healthSprite.setTexture(textures::healthSpriteTexture);
	this->healthSprite.setTextureRect(sf::IntRect (0, 0, 25, 7));
}

Player::~Player()
{

}

void Player::eightWayMovement(double time)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) // up
	{
		move(North);
		if (time > 1.0)
		{
			if (this->)
			{

			}
			else
			{

			}
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) // down
	{
		move(South);
		this->setTexture(textures::playerIdleDown);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) // left
	{
		move(West);
		this->setTexture(textures::playerIdleSide);
		this->setScale(-10,16);
		this->setPosition(getPosition().x + 10, getPosition().y); // this flips the sprite but requires the position to be moved. 
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) // right
	{
		move(East);
		this->setTexture(textures::playerIdleSide);
	}
}

void Player::update(double time)
{
	eightWayMovement(time);
	healthSprite.setPosition(this->getPosition().x - 12.5, this->getPosition().y - 23);
}