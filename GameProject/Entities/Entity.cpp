//
// Created by kevin on 22.10.2021.
//
#include "../Head Files/PreCompiledHeaders.h"
#include "Entity.h"


void Entity::initVariables()
{
    this->hitBoxComponent = nullptr;
    this->movementComponent = nullptr;
    this->animationComponent = nullptr;
}

Entity::Entity()
{
    this->initVariables();
}

Entity::~Entity()
{
    delete this->hitBoxComponent;
    delete this->movementComponent;
    delete this->animationComponent;
}

//Component functions
void Entity::setTexture(sf::Texture& texture)
{
    this->sprite.setTexture(texture);
}

void Entity::createHitBoxComponent(sf::Sprite & sprite,
                                   float offset_x, float offset_y,
                                   float width, float height)
{
    this->hitBoxComponent = new HitBoxComponent(sprite, offset_x, offset_y, width, height);
}

void Entity::createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration)
{
    this->movementComponent = new MovementComponent(this->sprite, maxVelocity, acceleration, deceleration);
}

void Entity::createAnimationComponent(sf::Texture & texture_sheet)
{
    this->animationComponent = new AnimationComponent(this->sprite, texture_sheet);
}

const sf::Vector2f & Entity::getPosition() const
{
    if (this->hitBoxComponent)
        return this->hitBoxComponent->getPosition();

    return this->sprite.getPosition();
}

const sf::Vector2u Entity::getGridPosition(const unsigned gridSizeU) const
{
    if (this->hitBoxComponent)
        return sf::Vector2u(
                static_cast<unsigned>(this->hitBoxComponent->getPosition().x) / gridSizeU,
                static_cast<unsigned>(this->hitBoxComponent->getPosition().y) / gridSizeU
        );

    return sf::Vector2u(
            static_cast<unsigned>(this->sprite.getPosition().x) / gridSizeU,
            static_cast<unsigned>(this->sprite.getPosition().y) / gridSizeU
    );
}

const sf::FloatRect Entity::getGlobalBounds() const
{
    if (this->hitBoxComponent)
        return this->hitBoxComponent->getGlobalBounds();

    return this->sprite.getGlobalBounds();
}

const sf::FloatRect Entity::getNextPositionBounds(const float& dt) const
{
    if (this->hitBoxComponent && this->movementComponent)
        return this->hitBoxComponent->getNextPosition(this->movementComponent->getVelocity() * dt);

    return sf::FloatRect(-1.f, -1.f, -1.f, -1.f);
}

//Functions
void Entity::setPosition(const float x, const float y)
{
    if (this->hitBoxComponent)
        this->hitBoxComponent->setPosition(x, y);
    else
        this->sprite.setPosition(x, y);
}

void Entity::move(const float dir_x, const float dir_y, const float& dt)
{
    if (this->movementComponent)
        this->movementComponent->move(dir_x, dir_y, dt); //Sets velocity
}

void Entity::noVelocity()
{
    if (this->movementComponent)
        this->movementComponent->noVelocity();

}

void Entity::noVelocityX()
{
    if (this->movementComponent)
        this->movementComponent->noVelocityX();
}

void Entity::noVelocityY()
{
    if (this->movementComponent)
        this->movementComponent->noVelocity();
}

void Entity::update(const float & dt)
{

}

void Entity::render(sf::RenderTarget& target)
{

}