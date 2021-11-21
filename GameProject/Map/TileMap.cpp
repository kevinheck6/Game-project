//
// Created by kevin on 20.11.2021.
//
#include "../Head Files/PreCompiledHeaders.h"
#include "TileMap.h"

TileMap::TileMap(float gridSize, unsigned width, unsigned height) {
    this->gridSizeF = gridSize;
    this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
    this->mapSize.x = width;
    this->mapSize.y = height;
    this->layers = 1;

    this->map.resize(this->mapSize.x, std::vector<std::vector<Tile*>>());
    for (size_t x = 0; x < this->mapSize.x ; ++x) {
        for (size_t y = 0; y < mapSize.y; ++y) {
            this->map[x].resize(this->mapSize.y, std::vector<Tile*>());
            for (size_t z = 0; z < layers; ++z) {
                this->map[x][y].resize(this->layers, nullptr);
            }
        }
    }
    if(!this->tileTexture.loadFromFile("../Resources/Images/TextureGround/grass1.jpg")) {
        std::cout << "ERROR::TILEMAP - FAIL TO LOAD TILE TEXTURE" << "\n";
    };
}

TileMap::~TileMap() {
    for (size_t x = 0; x < this->mapSize.x ; ++x) {
        for (size_t y = 0; y < mapSize.y; ++y) {
            for (size_t z = 0; z < layers; ++z) {
                delete this->map[x][y][z];
            }
        }
    }
}

//Functions
void TileMap::addTile(const unsigned x, const unsigned y, const unsigned z) {
//Take X, Y and Z from mouse Grid and ADD a tile to that position if internal tileMap array allows it
    if (x >= 0 && (x < this->mapSize.x) &&
        y >= 0 && (y < this->mapSize.y) &&
        z >= 0 && (z < layers)) {
        if(this->map[x][y][z] == nullptr) { // So we can ADD the tile
            this->map[x][y][z] = new Tile(x * this->gridSizeF, y * this->gridSizeF,
                                          this->gridSizeF, this->tileTexture);
            std::cout << "DEBUG - ADDED A TILE!" << "\n";
        }
    }
}

void TileMap::removeTile(const unsigned x, const unsigned y, const unsigned z) {
//Take X, Y and Z from mouse Grid and REMOVE a tile to that position if internal tileMap array allows it
    if (x >= 0 && (x < this->mapSize.x) &&
        y >= 0 && (y < this->mapSize.y) &&
        z >= 0 && (z < layers)) {
        if(this->map[x][y][z] != nullptr) { // So we can REMOVE the tile
            delete this->map[x][y][z];
            this->map[x][y][z] = nullptr;
            std::cout << "DEBUG - REMOVED A TILE!" << "\n";
        }
    }
}

void TileMap::update() {

}

void TileMap::render(sf::RenderTarget &target) {
    for (auto &x : this->map) {
        for (auto &y : x) {
            for (auto *z : y) {
                if (z != nullptr) {
                    z->render(target);
                }
            }
        }
    }
}



