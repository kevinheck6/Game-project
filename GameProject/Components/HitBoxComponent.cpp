//
// Created by kevin on 29.10.2021.
//
#include "../Head Files/PreCompiledHeaders.h"
#include "HitBoxComponent.h"

HitBoxComponent::HitBoxComponent(sf::Sprite& sprite,
                                 float offset_x, float offset_y,
                                 float width, float height)
                                 : sprite(sprite), offsetX(offset_x), offsetY(offset_y) {

    this->hitBox.setPosition(this->sprite.getPosition().x + offset_x,
                             this->sprite.getPosition().y + offset_y);
    this->hitBox.setSize(sf::Vector2f(width, height));
    this->hitBox.setFillColor(sf::Color::Transparent);
    this->hitBox.setOutlineThickness(1.f);
    this->hitBox.setOutlineColor(sf::Color::Green);
}

HitBoxComponent::~HitBoxComponent() {

}

//Accessors
const sf::Vector2f &HitBoxComponent::getPosition() const {
    return this->hitBox.getPosition();
}

const sf::FloatRect HitBoxComponent::getGlobalBounds() const {
    return this->hitBox.getGlobalBounds();
}

//Modifiers
void HitBoxComponent::setPosition(const sf::Vector2f& position) {
    this->hitBox.setPosition(position);
    this->sprite.setPosition(position.x - this->offsetX,
                             position.y - this->offsetY);
}

void HitBoxComponent::setPosition(const float x, const float y) {
    this->hitBox.setPosition(x, y);
    this->sprite.setPosition(x - this->offsetX,
                             y - this->offsetY);
}

//Functions
bool HitBoxComponent::intersection(const sf::FloatRect &fRect) {

    return this->hitBox.getGlobalBounds().intersects(fRect);
}

void HitBoxComponent::update() {
    this->hitBox.setPosition(this->sprite.getPosition().x + this->offsetX,
                             this->sprite.getPosition().y + this->offsetY);
}

void HitBoxComponent::render(sf::RenderTarget &target) {
    target.draw(this->hitBox);

}









