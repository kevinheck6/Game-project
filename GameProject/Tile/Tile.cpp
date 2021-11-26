//
// Created by kevin on 13.11.2021.
//
#include "../Head Files/PreCompiledHeaders.h"
#include "Tile.h"

Tile::Tile() {
    this->collision = false;
    this->type = 0;
}

Tile::Tile(unsigned grid_x, unsigned grid_y, float gridSizeF, const sf::Texture& texture, const sf::IntRect& rectangle_texture,
           bool collision, short type) {
    this->tile.setSize(sf::Vector2f(gridSizeF, gridSizeF));
    this->tile.setFillColor(sf::Color(255,255,255, 255));
    //this->tile.setOutlineThickness(1.f); // Black lines to see each square
    //this->tile.setOutlineColor(sf::Color::Black);
    this->tile.setPosition(static_cast<float>(grid_x) * gridSizeF, static_cast<float>(grid_y) * gridSizeF );
    this->tile.setTexture(&texture);
    this->tile.setTextureRect(rectangle_texture);

    this->collision = collision;
    this->type = type;

}

Tile::~Tile() {

}


//Accessors
const bool &Tile::getCollision() const {
    return this->collision;
}

const sf::Vector2f &Tile::getPosition() const {
    return this->tile.getPosition();
}


//Functions
const std::string Tile::getString() const {
    std::stringstream stringStream;
    stringStream << this->tile.getTextureRect().left << " " << this->tile.getTextureRect().top << " " <<
    this->collision << " " << this->type;

    return stringStream.str();
}

void Tile::update() {

}

void Tile::render(sf::RenderTarget &target) {
    target.draw(this->tile);
}





