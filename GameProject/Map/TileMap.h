//
// Created by kevin on 20.11.2021.
//
#pragma once

#include "../Tile/Tile.h"

class TileMap {
private:

    float gridSizeF;
    unsigned gridSizeU;
    sf::Vector2u mapSize;
    unsigned layers;
    std::vector<std::vector<std::vector<Tile*>>> map; // the map is in form of (X, Y, Layer)
    std::string textureFile;
    sf::Texture tileTexture;

public:
    TileMap(float gridSize, unsigned width, unsigned height, std::string texture_file);
    virtual ~TileMap();

    //Accessors
    const sf::Texture* getTileTexture() const;

    //Functions
    void addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& rectangle_texture);
    void removeTile(const unsigned x, const unsigned y, const unsigned z);

    void saveFile(const std::string file_name);
    void loadFile(const std::string file_name);

    void update();
    void render(sf::RenderTarget& target);
};

