//
// Created by kevin on 20.11.2021.
//
#include "../Head Files/PreCompiledHeaders.h"
#include "TileMap.h"

void TileMap::clearMemory() {
    for (size_t x = 0; x < this->mapSize.x ; ++x) {
        for (size_t y = 0; y < this->mapSize.y; ++y) {
            for (size_t z = 0; z < this->layers; ++z) {
                delete this->map[x][y][z];
                this->map[x][y][z] = nullptr;
            }
            this->map[x][y].clear();
        }
        this->map[x].clear();
    }
    this->map.clear();
}

TileMap::TileMap(float gridSize, unsigned width, unsigned height, std::string texture_file) {
    this->gridSizeF = gridSize;
    this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
    this->mapSize.x = width;
    this->mapSize.y = height;
    this->layers = 1;
    this->textureFile = texture_file;

    this->map.resize(this->mapSize.x, std::vector<std::vector<Tile*>>());
    for (size_t x = 0; x < this->mapSize.x; ++x) {
        for (size_t y = 0; y < this->mapSize.y; ++y) {
            this->map[x].resize(this->mapSize.y, std::vector<Tile*>());
            for (size_t z = 0; z < this->layers; ++z) {
                this->map[x][y].resize(this->layers, nullptr);
            }
        }
    }
    if(!this->tileTexture.loadFromFile(texture_file)) {
        std::cout << "ERROR::TILEMAP - FAIL TO LOAD TILE TEXTURE : " << texture_file << "\n";
    };
}

TileMap::~TileMap() {
    this->clearMemory();
}

//Accessors
const sf::Texture *TileMap::getTileTexture() const {
    return &this->tileTexture;
}

//Functions
void TileMap::addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& rectangle_texture,
                      const bool& collision, const short& type) {
//Take X, Y and Z from mouse Grid and ADD a tile to that position if internal tileMap array allows it
    if (x >= 0 && (x < this->mapSize.x) &&
        y >= 0 && (y < this->mapSize.y) &&
        z >= 0 && (z < this->layers)) {
        if(this->map[x][y][z] == nullptr) { // So we can ADD the tile
            this->map[x][y][z] = new Tile(x, y, this->gridSizeF, this->tileTexture, rectangle_texture,
                                          collision, type);
            std::cout << "DEBUG - ADDED A TILE!" << "\n";
        }
    }
}

void TileMap::removeTile(const unsigned x, const unsigned y, const unsigned z) {
//Take X, Y and Z from mouse Grid and REMOVE a tile to that position if internal tileMap array allows it
    if (x >= 0 && (x < this->mapSize.x) &&
        y >= 0 && (y < this->mapSize.y) &&
        z >= 0 && (z < this->layers)) {
        if(this->map[x][y][z] != nullptr) { // So we can REMOVE the tile
            delete this->map[x][y][z];
            this->map[x][y][z] = nullptr;
            std::cout << "DEBUG - REMOVED A TILE!" << "\n";
        }
    }
}


void TileMap::saveFile(const std::string file_name) {
    //Save map in a text file
    /*
     General info:
     Size x, y
     gridSize
     layers
     texture file

     Tiles:
     gridPos x, y, z(the layer),Texture rect x, y, collision ,type
     */

    std::ofstream out_file;

    out_file.open(file_name);
    if(out_file.is_open()) {
        out_file << this->mapSize.x << " " << this->mapSize.y << "\n"
        << this->gridSizeU << "\n"
        << this->layers << "\n"
        << this->textureFile << "\n";

        for (size_t x = 0; x < this->mapSize.x ; ++x) {
            for (size_t y = 0; y < this->mapSize.y; ++y) {
                for (size_t z = 0; z < this->layers; ++z) {
                    if(this->map[x][y][z]) {
                        out_file << x << " " << y << " " << z << " " <<
                        this->map[x][y][z]->getString() << " "; // Have to take care for the
                                                                            // last space not be saved
                    }
                }
            }
        }

    } else {
        std::cout << "Error::TileMap.cpp - Problem to Save file : " << file_name << "\n";
    }

    out_file.close();
}

void TileMap::loadFile(const std::string file_name) {

    std::ifstream in_file;

    in_file.open(file_name);
    if(in_file.is_open()) {
        sf::Vector2u size;
        unsigned gridSize = 0;
        unsigned layers = 0;
        std::string texture_file = "";
        unsigned x = 0;
        unsigned y = 0;
        unsigned z = 0;
        unsigned texture_rectX = 0;
        unsigned texture_rectY = 0;
        bool collision = false;
        short type = 0;


        //General info
        in_file >> size.x >> size.y >> gridSize >> layers >> texture_file;

        //Tiles

        this->gridSizeF = static_cast<float>(gridSize);
        this->gridSizeU = gridSize;
        this->mapSize.x = size.x;
        this->mapSize.y = size.y;
        this->layers = layers;
        this->textureFile = texture_file;

        this->clearMemory();

        this->map.resize(this->mapSize.x, std::vector<std::vector<Tile*>>());
        for (size_t x = 0; x < this->mapSize.x; ++x) {
            for (size_t y = 0; y < this->mapSize.y; ++y) {
                this->map[x].resize(this->mapSize.y, std::vector<Tile*>());
                for (size_t z = 0; z < this->layers; ++z) {
                    this->map[x][y].resize(this->layers, nullptr);
                }
            }
        }
        if(!this->tileTexture.loadFromFile(texture_file)) {
            std::cout << "ERROR::TILEMAP - FAIL TO LOAD TILE TEXTURE : " << texture_file << "\n";
        };

        //Load the Tiles
        while(in_file >> x >> y >> z >> texture_rectX >> texture_rectY >> collision >> type) {
            this->map[x][y][z] =new Tile(
                    x, y, this->gridSizeF,
                    this->tileTexture,
                    sf::IntRect(texture_rectX, texture_rectY,this->gridSizeU, this->gridSizeU),
                    collision,
                    type);
        }

    } else {
        std::cout << "Error::TileMap.cpp - Problem to Load file : " << file_name << "\n";
    }

    in_file.close();
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






