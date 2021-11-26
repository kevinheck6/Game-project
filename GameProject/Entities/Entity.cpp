//
// Created by kevin on 22.10.2021.
//
#include "../Head Files/PreCompiledHeaders.h"
#include "Entity.h"

void Entity::initVariables() {
    this->hitBoxComponent = nullptr;
    this->movementComponent = nullptr;
    this->animationComponent = nullptr;
}

Entity::Entity() {
    this->initVariables();
}

Entity::~Entity() {
    delete this->hitBoxComponent;
    delete this->movementComponent;
    delete this->animationComponent;
}

//Components Functions
void Entity::setTexture(sf::Texture& texture) {

    this->sprite.setTexture(texture);
}

void Entity::createHitBoxComponent(sf::Sprite& sprite,
                                   float offset_x, float offset_y,
                                   float width, float height) {

    this->hitBoxComponent = new HitBoxComponent(sprite, offset_x, offset_y, width, height);
}

void Entity::createMovementComponent(const float maxVelocity,
                                     const float acceleration, const float deceleration) {
    this->movementComponent = new MovementComponent(this->sprite, maxVelocity, acceleration, deceleration);
}

void Entity::createAnimationComponent(sf::Texture &texture_sheet) {
    this->animationComponent = new AnimationComponent(this->sprite, texture_sheet);
}

//Accessors
const sf::Vector2f &Entity::getPosition() const {
    if(this->hitBoxComponent) {
        return this->hitBoxComponent->getPosition();
    }
    return this->sprite.getPosition();
}

const sf::FloatRect Entity::getGlobalBounds() const {
    if(this->hitBoxComponent) {
        return this->hitBoxComponent->getGlobalBounds();
    }
    return this->sprite.getGlobalBounds();
}

//Functions
void Entity::setPosition(const float x, const float y) {
    if(this->hitBoxComponent) {
        return this->hitBoxComponent->setPosition(x, y);
    } else {
        this->sprite.setPosition(x, y);
    }
}

void Entity::move(const float dir_x, const float dir_y, const float& dt) {
    if(this->movementComponent) {
        this->movementComponent->move(dir_x, dir_y, dt); // Sets velocity
    }
}




















