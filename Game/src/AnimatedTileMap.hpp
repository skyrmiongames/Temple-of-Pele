#include <vector>
#include "TileMap.hpp"

/*
 * Created by Stuart Irwin on 4/17/2019.
 * Builds animations out of tilemaps
 */

class AnimatedTileMap : public sf::Drawable, public sf::Transformable {
private:
	std::vector<TileMap> tilemaps;
	int frame = 0;
	int maxFrames;
	double lastTime = 0;

	//Draw selected tilemap
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(tilemaps[frame]);
    }

public:
	//Build tilemap list
	bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, int frames) {
		maxFrames = frames - 1;
		int tileCount = GridMaker::WIDTH * GridMaker::HEIGHT;

		//Copy tile index list
		int* indexes = new int[tileCount];
		for(int i = 0; i < tileCount; i++)
			indexes[i] = tiles[i];

		//Build each frame
		for(int i = 0; i < frames; i++) {
			//Set next frame in tiles
			for(int j = 0; j < tileCount; j++)
				if(indexes[j] != -1)
					indexes[j] += 2;

			//Load tilemap
			TileMap *map = new TileMap();
		    if (!map->load(tileset, tileSize, indexes, GridMaker::WIDTH, GridMaker::HEIGHT))
		        return false;

		    //Add tilemap to list
		    tilemaps.push_back(*map);
		}
		delete indexes;
		return true;
	}

	//Update timer
	void update(double time) {

		//Every full second
		if(time - lastTime >= 0.5) {
			lastTime = time;
			frame++;

			//Reset to start frame
			if(frame == maxFrames)
				frame = 0;
		}
	}
};