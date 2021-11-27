//
// Created by kevin on 20.11.2021.
//
#pragma once

#include "../Tile/Tile.h"
#include "../Entities/Entity.h"

class Entity;
class Tile;

class TileMap {
private:
    void clearMemory();

    float gridSizeF;
    unsigned gridSizeU;
    sf::Vector2u mapSizeGrid;
    sf::Vector2f mapSizeWoldF;
    unsigned layers;
    std::vector<std::vector<std::vector<Tile*>>> map; // the map is in form of (X, Y, Layer)
    std::string textureFile;
    sf::Texture tileTexture;
    sf::RectangleShape collisionBox;

    //Culling
    int fromX;
    int toX;
    int fromY;
    int toY;
    int layer;

public:
    TileMap(float gridSize, unsigned width, unsigned height, std::string texture_file);
    virtual ~TileMap();

    //Accessors
    const sf::Texture* getTileTexture() const;

    //Functions
    void addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& rectangle_texture,
                 const bool& collision, const short& type);
    void removeTile(const unsigned x, const unsigned y, const unsigned z);

    void saveFile(const std::string file_name);
    void loadFile(const std::string file_name);

    void collisionChecker(Entity* entity, const float& dt);

    void update();
    void render(sf::RenderTarget& target, Entity* entity = nullptr);
};

