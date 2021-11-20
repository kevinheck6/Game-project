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
    std::vector<std::vector<std::vector<Tile>>> map; // the map is in form of (X, Y, Layer)
public:
    TileMap();
    virtual ~TileMap();

//Functions
    void update();
    void render(sf::RenderTarget& target);
};

