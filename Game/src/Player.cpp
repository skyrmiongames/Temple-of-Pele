#include "Player.h"

Player::Player() :Entity(60, 0, false, 1.2)
{
	//sf::IntRect playerRectangle(0,0 10, 16);
	this->setTexture(textures->playerIdleDown);
	this->healthSprite.setTexture(textures->healthSpriteTexture);
	this->healthSprite.setTextureRect(sf::IntRect (0, 0, 25, 7));
}

Player::~Player()
{

}

void Player::eightWayMovement(double time)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) // up
	{
		this->setTexture(textures->playerMoveUp);
		move(North);
		if (time > 1.0)
		{
			//if ()
			//{

			//}
			//else
			//{

			//}
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) // down
	{
		this->setTexture(textures->playerMoveDown);
		move(South);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) // left
	{
		this->setTexture(textures->playerMoveSide);
		move(West);
		this->setScale(-1,1);
		//this->setPosition(getPosition().x - 10, getPosition().y); // this flips the sprite but requires the position to be moved. 
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) // right
	{
		this->setTexture(textures->playerMoveSide);
		move(East);
	}
}

void Player::update(double time)
{
	eightWayMovement(time);
	healthSprite.setPosition(this->getPosition().x - 12.5, this->getPosition().y - 23);
}