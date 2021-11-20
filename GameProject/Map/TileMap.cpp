//
// Created by kevin on 20.11.2021.
//
#include "../Head Files/PreCompiledHeaders.h"
#include "TileMap.h"

TileMap::TileMap() {
    this->gridSizeU = 50;
    this->mapSize.x = 5000;
    this->mapSize.y = 5000;
    this->layers = 5;

    this->map.push_back(std::vector<std::vector<Tile>> ());
    for (size_t x = 0; x < this->mapSize.x ; ++x) {
        for (size_t y = 0; y < mapSize.y; ++y) {
            this->map[x].push_back(std::vector<Tile>());

            for (size_t z = 0; z < layers; ++z) {
                this->map[x][y].push_back(Tile());
            }
        }
        
    }
}

TileMap::~TileMap() {

}
