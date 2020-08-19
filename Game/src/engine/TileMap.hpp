#pragma once

#include <stdexcept>

#include "Node.h"
#include "GridMaker.h"

/*
 * Based off of sfml tutorial
 */

class TileMap : public Node {
private:
    const int tileX;
    const int tileY;
    Indexer indexes;

    //Graphical variables
    sf::VertexArray m_vertices;
    sf::Texture m_tileset;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.transform *= getTransform();
        states.texture = &m_tileset;
        target.draw(m_vertices, states);
    }

public:
    TileMap(const std::string& tileset, int new_tileX, int new_tileY, Indexer new_indexes, unsigned char layer = 0, int offset = 0)
     : Node(layer), tileX(new_tileX), tileY(new_tileY), indexes(new_indexes) {
        // load the tileset texture
        if(!m_tileset.loadFromFile(tileset))
            throw std::invalid_argument("Tilemap texture not found: " + tileset);

        //Set sizing
        unsigned int width = indexes.getSize().x;
        unsigned int height = indexes.getSize().y;
        setSize(sf::Vector2i(tileX * width, tileY * height));
        setOrigin(0, 0);

        // resize the vertex array to fit the level size
        m_vertices.setPrimitiveType(sf::Quads);
        m_vertices.resize(width * height * 4);

        //Load textures
        reload(offset);
    }

    void reload(int offset = 0) {
        unsigned int width = indexes.getSize().x;
        unsigned int height = indexes.getSize().y;
        int *tiles = indexes.indexGrid();
        int numTextures = (m_tileset.getSize().x / tileX) * (m_tileset.getSize().y / tileY);

        // populate the vertex array, with one quad per tile
        for(unsigned int i = 0; i < width; ++i)
            for(unsigned int j = 0; j < height; ++j) {
                // get the current tile number
                int tileNumber = (tiles[i + j * width] % numTextures) + offset;
                int rotations = (tiles[i + j * width] / numTextures);

                // find its position in the tileset texture
                int tu = tileNumber % (m_tileset.getSize().x / tileX);
                int tv = tileNumber / (m_tileset.getSize().x / tileX);

                // get a pointer to the current tile's quad
                sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

                if(tileNumber - offset != -1) {
                    // define its 4 texture coordinates
                    quad[(0 + rotations) % 4].texCoords = sf::Vector2f(tu * tileX, tv * tileY);
                    quad[(1 + rotations) % 4].texCoords = sf::Vector2f((tu + 1) * tileX, tv * tileY);
                    quad[(2 + rotations) % 4].texCoords = sf::Vector2f((tu + 1) * tileX, (tv + 1) * tileY);
                    quad[(3 + rotations) % 4].texCoords = sf::Vector2f(tu * tileX, (tv + 1) * tileY);

                    // define its 4 corners
                    quad[0].position = sf::Vector2f(i * tileX, j * tileY);
                    quad[1].position = sf::Vector2f((i + 1) * tileX, j * tileY);
                    quad[2].position = sf::Vector2f((i + 1) * tileX, (j + 1) * tileY);
                    quad[3].position = sf::Vector2f(i * tileX, (j + 1) * tileY);
                } else {
                    quad[0].position = sf::Vector2f(0, 0);
                    quad[1].position = sf::Vector2f(0, 0);
                    quad[2].position = sf::Vector2f(0, 0);
                    quad[3].position = sf::Vector2f(0, 0);
                }
            }
    }
};