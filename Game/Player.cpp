#include "src\Player.h"

Player::Player(double x_velocity,
	double y_velocity) //:Entity(60, 0, false, 1.2)
{
	
	this->x_velocity = 0.0;
	this->y_velocity = 0.0;
	
	sf::Texture upIdlePlayer;
	upIdlePlayer.loadFromFile("resources/Player_IdleUp.png");
	this->setTexture(upIdlePlayer);
	//sf::Sprite playerSprite;
	//playerSprite.setTexture(upIdlePlayer);

	sf::Texture healthSpriteTexture;
	healthSpriteTexture.loadFromFile("resources/Health_HeartsGif.png");
	this->healthSprite.setTexture(healthSpriteTexture);
}

Player::~Player()
{

}

void Player::eightWayMovement()
{
	if (sf::Keyboard::W) // up
	{
		if (this->getPosition().y >= 16)
		{
			this->setPosition(getPosition().x, getPosition().y - 16);
			//this->setTexture();
		}
		else
		{

		}
	}
	else if (sf::Keyboard::S) // down
	{
		if (this->getPosition().y >= 384)
		{
			this->setPosition(getPosition().x, getPosition().y + 16);
		}
		else
		{

		}
	}
	else if (sf::Keyboard::A) // left
	{
		if (this->getPosition().x >= 16)
		{
			this->setPosition(getPosition().x - 16, getPosition().y);
		}
		else
		{

		}
	}
	else if (sf::Keyboard::D) // right
	{
		if (this->getPosition().x >= 584)
		{
			this->setPosition(getPosition().x + 16, getPosition().y);
		}
		else
		{

		}
	}
}

void Player::slowDown()
{

}