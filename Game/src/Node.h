#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "enums.h"

/*
 * Created by Stuart Irwin on 4/13/2019.
 * Sprite with collision
 */

class Node : public sf::Sprite {
private:
	CollisionLayer layer;
	sf::Vector2i size;

public:
	Node(CollisionLayer layer=ENEMY, size=(new Vector2i(1, 1)));

	//Collision engine
	CollisionLayer get_layer();
	bool on_screen();
	bool check_collision(Node *other);

	//Entity implementation
	virtual void on_load();
	virtual void update();
	virtual void collide(CollisionLayer layer, Node *object);
};