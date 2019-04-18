#include "Player.h"

Player::Player() :Entity(60, 0, false, 1.2)
{
	//sf::IntRect playerRectangle(0,0 10, 16);
	this->setTexture(textures->playerIdleDown);
	this->healthSprite.setTexture(textures->healthSpriteTexture);
	this->healthSprite.setTextureRect(sf::IntRect (0, 0, 25, 7));
	this->hasKey = false;
	int curDirection = 0; // 0 is down, 1 is up, 2 is right, 3 is left
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
		this->curDirection = 1;
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
		this->curDirection = 0;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) // left
	{
		this->setTexture(textures->playerMoveLeft);
		move(West);
		this->curDirection = 3;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) // right
	{
		this->setTexture(textures->playerMoveRight);
		move(East);
		this->curDirection = 2;
	}
}

void Player::drawGUI(sf::RenderWindow &window)
{
	window.draw(healthSprite);
}

void Player::updateHealth()
{
	healthSprite.setPosition(this->getPosition().x - 8, this->getPosition().y - 16);

	if (this->health >= 40)
	{
		healthSprite.setTextureRect(sf::IntRect(0, 0, 25, 7));
	}
	else if (this->health >= 20)
	{
		healthSprite.setTextureRect(sf::IntRect(0, 7, 25, 7));
	}
	else if (this->health >= 0)
	{
		healthSprite.setTextureRect(sf::IntRect(0, 14, 25, 7));
	}
	else
	{
		this->is_dead();
	}
}

void Player::updateKey()
{
	
}

void Player::attack()
{
	if (this->curDirection == 0) // face down
	{

	}
	else if (this->curDirection == 1) // face up
	{

	}
	else if (this->curDirection == 3) // face left
	{

	}
	else if (this->curDirection == 2) // face right
	{

	}
}

void Player::update(double time)
{
	eightWayMovement(time);
	updateHealth();
	updateKey();
}