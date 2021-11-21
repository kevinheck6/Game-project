//
// Created by kevin on 13.11.2021.
//
#include "../Head Files/PreCompiledHeaders.h"
#include "Tile.h"

Tile::Tile() {

}

Tile::Tile(float x, float y, float gridSizeF, const sf::Texture& texture, const sf::IntRect& rectangle_texture) {
    this->tile.setSize(sf::Vector2f(gridSizeF, gridSizeF));
    this->tile.setFillColor(sf::Color(255,255,255, 255));
    //this->tile.setOutlineThickness(1.f); // Black lines to see each square
    //this->tile.setOutlineColor(sf::Color::Black);
    this->tile.setPosition(x, y);
    this->tile.setTexture(&texture);
    this->tile.setTextureRect(rectangle_texture);

}

Tile::~Tile() {

}

//Functions
void Tile::update() {

}

void Tile::render(sf::RenderTarget &target) {
    target.draw(this->tile);
}


