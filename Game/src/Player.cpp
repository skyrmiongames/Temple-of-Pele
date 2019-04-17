#include "Player.h"

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
		move(North);
		//this->setTexture();
	}
	else if (sf::Keyboard::S) // down
	{
		move(South);
	}
	else if (sf::Keyboard::A) // left
	{
		move(West);
	}
	else if (sf::Keyboard::D) // right
	{
		move(East);
	}
}

void Player::update()
{

}