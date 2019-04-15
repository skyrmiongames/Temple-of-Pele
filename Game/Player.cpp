#include "src\Player.h"

Player::Player(double x_velocity,
	double y_velocity) :Entity(60, 0, false, 1.2)
{
	this->x_velocity = 0.0;
	this->y_velocity = 0.0;
	this->setTexture();
}

Player::~Player()
{

}

void Player::eightWayMovement()
{

}

void Player::slowDown()
{

}