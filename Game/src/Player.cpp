#include "Player.h"

Player::Player() :Entity(60, 0, false, 1.2, PLAYER, sf::Vector2i(10, 16))
{
	//sf::IntRect playerRectangle(0,0 10, 16);
	this->setTexture(textures->playerIdleDown);
	this->healthSprite.setTexture(textures->healthSpriteTexture);
	this->healthSprite.setTextureRect(sf::IntRect (0, 0, 25, 7));
	this->hasKey = false;
	curDirection = 0; // 0 is down, 1 is up, 2 is right, 3 is left
	knife = Node(SWORD, sf::Vector2i(10, 10));
	knife.setPosition(-10,10);
	knife.setTexture(textures->knife);

	lastAniTime = 0.0;
	lastDamageTime = 0.0;
	curMoveFrame = 0;

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
		move(PI/2);
		//move(North);
		this->curDirection = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) // down
	{
		move(-PI/2);
		//move(South);
		this->curDirection = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) // left
	{
		move(PI);
		/*move(East);*/
		this->curDirection = 3;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) // right
	{
		move(0);
		/*move(West);*/
		this->curDirection = 2;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::A)) // up-left
	{
		move(PI/4);
		/*move(Northwest);*/
		this->curDirection = 3;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::D)) // up-right
	{
		move((3 * PI) / 4);
		/*move(Northeast);*/
		this->curDirection = 2;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::A)) // down-left
	{
		move((3 * PI) / 4);
		/*move(Southwest);*/
		this->curDirection = 3;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::D)) // down-right
	{
		move((5 * PI) / 4);
		/*move(Southeast);*/
		this->curDirection = 2;
	}
}

void Player::updateFrameTime(double time, int curFrame, int maxMoveFrames)
{
	if (time - lastAniTime >= 0.1)
	{
		lastAniTime = time;
		curMoveFrame++;
		if (curFrame == maxMoveFrames)
		{
			curMoveFrame = 0;
		}
	}
}

void Player::updateTakeDamageTime(double time)
{
	if (time - lastDamageTime >= 1)
	{
		lastDamageTime = time;
		this->invulnerable = false;
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
			updateFrameTime(time, curMoveFrame, maxMoveFrames);
			this->setTexture(textures->playerMoveUp);
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
			maxMoveFrames = 4;
			updateFrameTime(time, curMoveFrame, maxMoveFrames);
			this->setTexture(textures->playerMoveDown);
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
		else if (curDirection == 3) // left
		{
			maxMoveFrames = 5;
			updateFrameTime(time, curMoveFrame, maxMoveFrames);
			this->setTexture(textures->playerMoveLeft);
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
			case 4:
				this->setTextureRect(sf::IntRect(10, 16, 10, 16));
				break;
			}
		}
		else if (curDirection == 2) // right
		{
			maxMoveFrames = 5;
			updateFrameTime(time, curMoveFrame, maxMoveFrames);
			this->setTexture(textures->playerMoveRight);
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
			case 4:
				this->setTextureRect(sf::IntRect(10, 16, 10, 16));
				break; 
			}
		}
	}
	else
	{
		this->setTextureRect(sf::IntRect(0, 0, 10, 16));
		if (curDirection == 0) // down
		{
			this->setTexture(textures->playerIdleDown);
		}
		else if (curDirection == 1) // up
		{
			this->setTexture(textures->playerIdleUp);
		}
		else if (curDirection == 2) // right 
		{
			this->setTexture(textures->playerIdleRight);
		}
		else if (curDirection == 3) // left
		{
			this->setTexture(textures->playerIdleLeft);
		}
	}
}

void Player::drawGUI(sf::RenderWindow &window)
{
	window.draw(*this);
	window.draw(healthSprite);
	window.draw(knife);
}

void Player::drawView(sf::RenderWindow &window)
{
	viewPlayer.setCenter(getPosition().x, getPosition().y);
	window.setView(viewPlayer);
}

void Player::takeDamage(double time)
{
	this->invulnerable = true;
	updateTakeDamageTime(time);
	modify_health(-20);
	switch (curDirection) // push back for when getting injured. 
	{
	case 0: setPosition(getPosition().x, getPosition().y - 5);
		break; // up
	case 1: setPosition(getPosition().x, getPosition().y + 5);
		break; // down
	case 2: setPosition(getPosition().x - 5, getPosition().y);
		break; // right
	case 3: setPosition(getPosition().x + 5, getPosition().y);
		break; // left
	}
}

void Player::updateHealth(double time)
{
	if (GridMaker::check_tile(getPosition()) == EMPTY)
	{
		takeDamage(time);
	}

	healthSprite.setPosition(this->getPosition().x - 12.5, this->getPosition().y - 16);

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
		healthSprite.setTextureRect(sf::IntRect(0, 21, 25, 7));
		die();
	}
}
void Player::die()
{
	endGame = true;
	EndScreen *object = new EndScreen(false);
	UpdateList::add_node(object);

	viewPlayer.setSize(sf::Vector2f(600, 400));
	setPosition(3000, 80);
	object->activate();
}

void Player::attack()
{
 	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (this->curDirection == 0) // face down
		{
			knife.setRotation(180);
			knife.setPosition(this->getPosition().x + 2, this->getPosition().y + 16);
		}
		else if (this->curDirection == 1) // face up
		{
			knife.setRotation(0);
			knife.setPosition(this->getPosition().x - 2, this->getPosition().y - 16);
		}
		else if (this->curDirection == 3) // face left
		{
			knife.setRotation(270);
			knife.setPosition(this->getPosition().x - 12, this->getPosition().y + 2);
		}
		else if (this->curDirection == 2) // face right
		{
			knife.setRotation(90);
			knife.setPosition(this->getPosition().x + 12, this->getPosition().y - 2);
		}
	} else {
		knife.setRotation(0.f);
		knife.setPosition(0, 1000);
	}
}

void Player::update(double time)
{
	if(!endGame) {
		attack();
		eightWayMovement(time);
		updateHealth(time);
	}
}

void Player::collide(Node *object , double time) 
{
	//Pickup key object
	if(object->get_layer() == KEY && hasKey == false) {
		hasKey = true;
		object->activate();
	}

	if (object->get_layer() == ENEMY, object->get_layer() == FIREBALL)
	{
		takeDamage(time);
	}

	//Show full end screen
	if(object->get_layer() == ENDSCREEN) {
		viewPlayer.setSize(sf::Vector2f(600, 400));
		endGame = true;
		setPosition(3000,80);
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