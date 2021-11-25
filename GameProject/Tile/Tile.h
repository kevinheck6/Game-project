//
// Created by kevin on 13.11.2021.
//
#pragma once

enum TileTypes {DEFAULT = 0};

class Tile {
private:
protected:
    sf::RectangleShape tile;
    bool collision;
    short unsigned type; // Maybe will have to be only short type

public:
    Tile();
    Tile(unsigned grid_x, unsigned grid_y, float gridSizeF, const sf::Texture& texture, const sf::IntRect& rectangle_texture,
         bool collision = false, short type = TileTypes::DEFAULT);
    virtual ~Tile();

    //Functions
    const std::string getString() const;

    void update();
    void render(sf::RenderTarget& target);

};


