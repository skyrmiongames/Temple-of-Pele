#include "Player.h"

Player::Player() :Entity(60, 0, false, 1.2, PLAYER, sf::Vector2i(10, 16))
{
	//sf::IntRect playerRectangle(0,0 10, 16);
	this->setTexture(textures->playerIdleDown);
	this->healthSprite.setTexture(textures->healthSpriteTexture);
	this->healthSprite.setTextureRect(sf::IntRect (0, 0, 25, 7));
	this->hasKey = false;
	int curDirection = 0; // 0 is down, 1 is up, 2 is right, 3 is left
	knife = new Node(SWORD);
	knife->setPosition(-10,10);
	knife->setTexture(textures->knife);

	double lastTime = 0.0;
	int curMoveFrame = 0;

	viewPlayer.setSize(sf::Vector2f(300, 200)); //= new sf::View(sf::Vector2f(this->getPosition().x, this->getPosition().y),
	viewPlayer.setCenter(sf::Vector2f(150, 100));
}

Player::~Player()
{

}

void Player::eightWayMovement(double time)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) // up
	{
		this->setTexture(textures->playerIdleUp);
		move(PI/2);
		//move(North);
		this->curDirection = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) // down
	{
		this->setTexture(textures->playerIdleDown);
		move(-PI/2);
		//move(South);
		this->curDirection = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) // left
	{
		this->setTexture(textures->playerIdleLeft);
		move(PI);
		/*move(East);*/
		this->curDirection = 3;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) // right
	{
		this->setTexture(textures->playerIdleRight);
		move(0);
		/*move(West);*/
		this->curDirection = 2;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::A)) // up-left
	{
		this->setTexture(textures->playerMoveLeft);
		move(PI/4);
		/*move(Northwest);*/
		this->curDirection = 3;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::D)) // up-right
	{
		this->setTexture(textures->playerMoveRight);
		move((3 * PI) / 4);
		/*move(Northeast);*/
		this->curDirection = 2;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::A)) // down-left
	{
		this->setTexture(textures->playerMoveLeft);
		move((3 * PI) / 4);
		/*move(Southwest);*/
		this->curDirection = 3;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::D)) // down-right
	{
		this->setTexture(textures->playerMoveRight);
		move((5 * PI) / 4);
		/*move(Southeast);*/
		this->curDirection = 2;
	}
	knife->setPosition(-10, 10);
}

void Player::updateTime(double time, int curFrame, int maxMoveFrames)
{
	if (time - lastTime >= 0.1)
	{
		lastTime = time;
		curFrame++;
		if (curFrame == maxMoveFrames)
		{
			curFrame = 0;
		}
	}
}

void Player::animatePlayer(double time)
{
	int maxMoveFrames = 0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if (curDirection == 1) //up
		{
			maxMoveFrames = 4;
			updateTime(time, curMoveFrame, maxMoveFrames);
			switch (curMoveFrame)
			{
			case 0:
				this->setTextureRect(sf::IntRect(0, 0, 10, 16));
				break;
			case 1:
				this->setTextureRect(sf::IntRect(10, 0, 10, 16));
				break;
			case 2:
				this->setTextureRect(sf::IntRect(20, 0, 10, 16));
				break;
			case 3:
				this->setTextureRect(sf::IntRect(0, 16, 10, 16));
				break;
			}
		}
		else if (curDirection == 0) // down
		{

		}
		else if (curDirection == 3) // left
		{

		}
		else if (curDirection == 2) // right
		{

		}
	}
}

void Player::drawGUI(sf::RenderWindow &window)
{
	window.draw(*this);
	window.draw(healthSprite);
}

void Player::drawView(sf::RenderWindow &window)
{
	viewPlayer.setCenter(getPosition().x, getPosition().y);
	window.setView(viewPlayer);
}

void Player::updateHealth()
{
	healthSprite.setPosition(this->getPosition().x - 15.4, this->getPosition().y - 16);

	if (this->health > 40)
	{
		healthSprite.setTextureRect(sf::IntRect(0, 0, 25, 7));
	}
	else if (this->health > 20)
	{
		healthSprite.setTextureRect(sf::IntRect(0, 7, 25, 7));
	}
	else if (this->health > 0)
	{
		healthSprite.setTextureRect(sf::IntRect(0, 14, 25, 7));
	}
	else
	{
		this->is_dead();
	}
}

void Player::attack()
{
 	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (this->curDirection == 0) // face down
		{
			knife->setRotation(180);
			knife->setPosition(this->getPosition().x, this->getPosition().y + 10);
		}
		else if (this->curDirection == 1) // face up
		{
			knife->setRotation(0);
			knife->setPosition(this->getPosition().x, this->getPosition().y - 10);
		}
		else if (this->curDirection == 3) // face left
		{
			knife->setRotation(90);
			knife->setPosition(this->getPosition().x - 5, this->getPosition().y);
		}
		else if (this->curDirection == 2) // face right
		{
			knife->setRotation(270);
			knife->setPosition(this->getPosition().x + 5, this->getPosition().y);
		} else {
			knife->setRotation(0.f);
			knife->setPosition(-10, 10);
		}
	}
}

void Player::update(double time)
{
	if(!endGame) {
		eightWayMovement(time);
		updateHealth();
	 	attack();
	}
}

void Player::collide(Node *object) 
{
	//Pickup key object
	if(object->get_layer() == KEY && hasKey == false) {
		hasKey = true;
		object->activate();
	}

	//Show full end screen
	if(object->get_layer() == ENDSCREEN) {
		viewPlayer.setSize(sf::Vector2f(600, 400));
		endGame = true;
		setPosition(1000,80);
		object->activate();
	}
}

bool Player::getKey()
{	
	//Use key if available
	if(hasKey) {
		hasKey = false;
		return true;
	}
	return false;
}