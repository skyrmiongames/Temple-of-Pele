#include <vector>
#include "TileMap.hpp"

/*
 * Created by Stuart Irwin on 4/17/2019.
 * Builds animations out of tilemaps
 */

class AnimatedTileMap : public Node {
private:
	std::vector<TileMap> tilemaps;
	int numTiles = 2;
	int maxFrames;
	int frame = 0;
	double lastTime = 0;
	double delay = -1;

	//Draw selected tilemap
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		states.transform *= getTransform();
		target.draw(tilemaps[frame], states);
    }

public:
	AnimatedTileMap(const std::string& tileset, int tileX, int tileY, Indexer indexes, int frames, unsigned char layer = 0) : Node(layer) {
		maxFrames = frames - 1;
		int width = indexes.getSize().x;
        int height = indexes.getSize().y;
		setSize(sf::Vector2i(tileX * width, tileY * height));
		setOrigin(0, 0);

		//Build each frame
		for(int i = 0; i < frames; i++) {
			//Load new tilemap
			TileMap *map = new TileMap(tileset, tileX, tileY, indexes, layer, i * numTiles);
		    tilemaps.push_back(*map);
		}
    }

	//Reload all tilemaps
	void reload() {
		for(int i = 0; i <= maxFrames; i++)
			tilemaps[i].reload(i * numTiles);
	}

	//Start animation
	void start(double delay, double time=0) {
		this->delay = delay;
		this->lastTime = time;
	}

	//Update timer
	void update(double time) {
		//Every half second
		if(delay > 0 && time - lastTime >= 0.5) {
			lastTime = time;
			frame++;

			//Reset to start frame
			if(frame == maxFrames)
				frame = 0;
		}
	}
};