#include <Sprite.hpp>
#include <Vector2.hpp>
#include <Texture.hpp>
#include <Rect.hpp>
#include "enums.h"

/*
 * Created by Stuart Irwin on 4/13/2019.
 * Sprite with collision and room integration
 */

class Node : public sf::Sprite {
private:
	CollisionLayer layer;
	int room;

public:
	Node(int room, sf::Vector2 position, sf::Texture texture, CollisionLayer layer);

	//Collision and room engine
	int get_room();
	void change_room(int room);
	TileType check_tile(sf::Vector2 position);
	bool check_collision(sf::IntRect rectangle, CollisionLayer layer);

	//Entity implementation
	virtual void on_load();
	virtual void update();
	virtual void collide(CollisionLayer layer, Node object);
}