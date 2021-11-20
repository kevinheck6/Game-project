//
// Created by kevin on 13.11.2021.
//
#include "../Head Files/PreCompiledHeaders.h"
#include "Tile.h"

Tile::Tile() {

}

Tile::Tile(float x, float y, float gridSizeF) {
    this->tile.setSize(sf::Vector2f(gridSizeF, gridSizeF));
    this->tile.setFillColor(sf::Color::Green);
    this->tile.setPosition(x, y);
}

Tile::~Tile() {

}

//Functions
void Tile::update() {

}

void Tile::render(sf::RenderTarget &target) {
    target.draw(this->tile);
}


