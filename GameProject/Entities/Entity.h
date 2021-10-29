#pragma once

#include "../Components/MovementComponent.h"
#include "../Components/AnimationComponent.h"
#include "../Components/HitBoxComponent.h"

class Entity {
private:
    void initVariables();

protected:
    sf::Sprite sprite;

    HitBoxComponent* hitBoxComponent;
    MovementComponent* movementComponent;
    AnimationComponent* animationComponent;

public:
    Entity();
    virtual ~Entity();

    //Components Functions
    void setTexture(sf::Texture& texture);
    void createHitBoxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height);
    void createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);
    void createAnimationComponent(sf::Texture& texture_sheet);

    //Functions
    void setPositions(const float x, const float y);
    virtual void move(const float x, const float y, const float& dt);

    virtual void update(const float& dt);
    virtual void render(sf::RenderTarget& target);
};

