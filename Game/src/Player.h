#pragma once

#include "Entity.h"

class Player : public Entity {
public:
	Player(
		double x_velocity = 0.0,
		double y_velocity = 0.0
	) : Entity() {
		this->x_velocity = 0.0;
		this->y_velocity = 0.0;
		sf::Texture upIdlePlayer;
		upIdlePlayer.loadFromFile("Player_IdleUp.png");
		//this->setTexture(upIdlePlayer);
		sf::Sprite playerSprite;
		playerSprite.setTexture(upIdlePlayer);
	};
	~Player();

	void eightWayMovement();
	void slowDown();

private:
	double x_velocity;
	double y_velocity;
};
