#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "enums.h"

/*
 * Created by Stuart Irwin on 4/13/2019.
 * Sprite with collision and room integration
 */

class Node : public sf::Sprite {
private:
	CollisionLayer layer;
	sf:Vector2i size;
	int room;

public:
	Node(int room, sf::Vector2i position, CollisionLayer layer);

	//Collision and room engine
	int get_room();
	TileType check_tile(sf::Vector2i position);
	bool check_collision(Node *other);

	//Entity implementation
	virtual void on_load();
	virtual void on_unload();
	virtual void update();
	virtual void collide(CollisionLayer layer, Node *object);
};