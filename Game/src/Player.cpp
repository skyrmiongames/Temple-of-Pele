#include "Player.h"

Player::Player() : Entity(PLAYER, sf::Vector2i(10, 16), 60, 0, false, 1.2) {
	//sf::IntRect playerRectangle(0,0 10, 16);
	this->setTexture(textures.playerIdleDown);

	// health display constructor
	healthSprite = Node(GUI, sf::Vector2i(25, 7), false, this);
	healthSprite.setPosition(0, -12.5);
	healthSprite.setTexture(textures.healthSpriteTexture);
	healthSprite.setTextureRect(sf::IntRect (0, 0, 25, 7));
	UpdateList::addNode(&healthSprite);

	// key constructor
	keyIcon = Node(GUI, sf::Vector2i(16, 16), true, this);
	keyIcon.setPosition(0, -24);
	keyIcon.setTexture(textures.key);
	UpdateList::addNode(&keyIcon);
	hasKey = false;

	// vertical knife constructor
	knifeV = Node(SWORD, sf::Vector2i(4, 11), false);
	knifeV.setPosition(-10,10);
	knifeV.setTexture(textures.knife);
	UpdateList::addNode(&knifeV);

	// horizontal knife constructor
	knifeH = Node(SWORD, sf::Vector2i(11, 4), false);
	knifeH.setPosition(-10, 10);
	knifeH.setTexture(textures.knife);
	UpdateList::addNode(&knifeH);

	// time members
	lastAniTime = 0.0;
	lastDamageTime = 0.0;

	// current movment frame
	curMoveFrame = 0;
	curDirection = 0; // 0 is down, 1 is up, 2 is right, 3 is left

	// setting player view size
	UpdateList::setCamera(this, sf::Vector2f(300, 200));

	// set collision layers
	collideWith(KEY);
	collideWith(ENEMY);
	collideWith(FIREBALL);
	collideWith(ENDSCREEN);
}

Player::~Player()
{

}

void Player::eightWayMovement(double time)
{
	sf::Vector2i direction;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) // up
	{
		direction.y++;
		this->curDirection = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) // down
	{
		direction.y--;
		this->curDirection = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) // left
	{
		direction.x--;
		this->curDirection = 3;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) // right
	{
		direction.x++;
		this->curDirection = 2;
	}

	if(direction.x != 0 || direction.y != 0)
		move(std::atan2(direction.y, direction.x));

	Entity::playerPos = getPosition();
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
			this->setTexture(textures.playerMoveUp);
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
			this->setTexture(textures.playerMoveDown);
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
			this->setTexture(textures.playerMoveLeft);
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
			this->setTexture(textures.playerMoveRight);
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
			this->setTexture(textures.playerIdleDown);
		}
		else if (curDirection == 1) // up
		{
			this->setTexture(textures.playerIdleUp);
		}
		else if (curDirection == 2) // right
		{
			this->setTexture(textures.playerIdleRight);
		}
		else if (curDirection == 3) // left
		{
			this->setTexture(textures.playerIdleLeft);
		}
	}
}

bool Player::updateTakeDamageTime(double time)
{
	bool isInvulnerable = true;
	if (time - lastDamageTime >= 1)
	{
		lastDamageTime = time;
		this->invulnerable = false;
	}
	return isInvulnerable;
}

void Player::setLastDamageTime(double newDamageTime)
{
	this->lastDamageTime = newDamageTime;
}

bool Player::takeDamage(double time)
{
	bool isInvulnerable = false;
	this->invulnerable = true;
	isInvulnerable = updateTakeDamageTime(time);
	modify_health(-20);
	if (GridMaker::check_tile(getPosition()) == EMPTY)
	{
		switch (curDirection) // push back for when getting injured.
		{
		case 0: setPosition(getPosition().x, getPosition().y - 1);
			break; // up
		case 1: setPosition(getPosition().x, getPosition().y + 1);
			break; // down
		case 2: setPosition(getPosition().x - 1, getPosition().y);
			break; // right
		case 3: setPosition(getPosition().x + 1, getPosition().y);
			break; // left
		}
	}
	return isInvulnerable;
}

void Player::updateHealth(double time)
{
	if (GridMaker::check_tile(getPosition()) == EMPTY)
	{
		takeDamage(time);
	}
	
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
	EndScreen *object = new EndScreen(textures, false);
	UpdateList::addNode(object);

	UpdateList::setCamera(this, sf::Vector2f(600, 400));
	setPosition(2000, 80);
	object->display();
}

void Player::attack()
{

 	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (this->curDirection == 0) // face down
		{
			knifeV.setRotation(180);
			knifeV.setPosition(this->getPosition().x , this->getPosition().y + 8);
		}
		else if (this->curDirection == 1) // face up
		{
			knifeV.setRotation(0);
			knifeV.setPosition(this->getPosition().x , this->getPosition().y - 8);
		}
		else if (curDirection != 0 || curDirection != 1)
		{
			knifeV.setRotation(0.f);
			knifeV.setPosition(0, 1000);
		}
		if (this->curDirection == 3) // face left
		{
			knifeH.setRotation(270);
			knifeH.setPosition(this->getPosition().x - 12, this->getPosition().y - 2);
		}
		else if (this->curDirection == 2) // face right
		{
			knifeH.setRotation(90);
			knifeH.setPosition(this->getPosition().x + 12, this->getPosition().y + 4);
		}
		else if (curDirection != 2 || curDirection != 3)
		{
			knifeH.setRotation(0.f);
			knifeH.setPosition(0, 1000);
		}
	}
	else
	{
		knifeH.setRotation(0.f);
		knifeH.setPosition(0, 1000);
		knifeV.setRotation(0.f);
		knifeV.setPosition(0, 1000);
	}
}

void Player::update(double time)
{
	if(!endGame) {
		attack();
		eightWayMovement(time);
		updateHealth(time);
		keyIcon.setHidden(!hasKey);
		animatePlayer(time);
	}
}

void Player::collide(Node *object , double time)
{
	if (object->getLayer() == ENEMY || object->getLayer() == FIREBALL)
	{
		takeDamage(time);
	}

	//Show full end screen
	if(object->getLayer() == ENDSCREEN) {
		UpdateList::setCamera(this, sf::Vector2f(600, 400));
		endGame = true;
		setPosition(2000,80);
		((EndScreen*)object)->display();
	}

	//Pickup key object
	if(object->getLayer() == KEY && hasKey == false) {
		hasKey = true;
		object->setDelete();
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

void Player::setKey(bool newHasKey)
{
	hasKey = newHasKey;
}