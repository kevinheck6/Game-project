//
// Created by kevin on 13.11.2021.
//
#pragma once

#include <iostream>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <sstream>

class Tile {
private:
protected:
    sf::RectangleShape tile;
public:
    Tile();
    Tile(float x, float y, float gridSizeF,const sf::Texture& texture, const sf::IntRect& rectangle_texture);
    virtual ~Tile();

    //Functions
    void update();
    void render(sf::RenderTarget& target);

};


