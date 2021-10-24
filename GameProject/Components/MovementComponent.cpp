//
// Created by kevin on 24.10.2021.
//

#include "MovementComponent.h"

MovementComponent::MovementComponent
(sf::Sprite& sprite,float maxVelocity, float acceleration, float deceleration) :
sprite(sprite), maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration) {

}

MovementComponent::~MovementComponent() {

}

const sf::Vector2f &MovementComponent::getVelocity() const {
    return this->velocity;
}

//Functions
void MovementComponent::move(const float dir_x, const float dir_y, const float& dt) {
    //Accelerating a sprite until max velocity
    //Acceleration
    this->velocity.x += this->acceleration * dir_x;

    if(this->velocity.x > 0.f) {//check for moving right
        if(this->velocity.x > this->maxVelocity) {
            this->velocity.x = this->maxVelocity;
        }
    } else if (this->velocity.x < 0.f) { //check for moving left
        if(this->velocity.x < -this->maxVelocity) {
            this->velocity.x = -this->maxVelocity;
        }
    }

    this->velocity.y += this->acceleration * dir_y;

}

void MovementComponent::update(const float &dt) {

    //Deceleration
    if (this->velocity.x > 0.f) { //check for right
        this->velocity.x -= deceleration;
        if(this->velocity.x < 0.f) {
            this->velocity.x = 0.f;
        }
    } else if(this->velocity.x < 0.f) {
        this->velocity.x += deceleration;
        if(this->velocity.x > 0.f) {
            this->velocity.x = 0.f;
        }
    }

    //Final Move
    this->sprite.move(this->velocity * dt); // Uses velocity
}




