//
// Created by kevin on 20.11.2021.
//
#include "../Head Files/PreCompiledHeaders.h"
#include "TileMap.h"

TileMap::TileMap() {
    this->gridSizeF = 100.f;
    this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
    this->mapSize.x = 10;
    this->mapSize.y = 10;
    this->layers = 1;

    this->map.resize(this->mapSize.x);
    for (size_t x = 0; x < this->mapSize.x ; ++x) {
        this->map.push_back(std::vector<std::vector<Tile>>());

        for (size_t y = 0; y < mapSize.y; ++y) {
            this->map[x].resize(this->mapSize.y);
            this->map[x].push_back(std::vector<Tile>());

            for (size_t z = 0; z < layers; ++z) {
                this->map[x][y].resize(this->layers);
                this->map[x][y].push_back(Tile(x * this->gridSizeF, y * this->gridSizeF, this->gridSizeF));
            }
        }
        
    }
}

TileMap::~TileMap() {
}


//Functions
void TileMap::update() {

}

void TileMap::render(sf::RenderTarget &target) {
    for (auto &x : this->map) {
        for (auto &y : x) {
            for (auto &z : y) {
                z.render(target);
            }
        }
    }
}


