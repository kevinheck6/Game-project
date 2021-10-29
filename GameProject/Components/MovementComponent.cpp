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
//Accessors
const float &MovementComponent::getMaxVelocity() const {
    return this->maxVelocity;
}

const sf::Vector2f &MovementComponent::getVelocity() const {
    return this->velocity;
}

//Functions
const bool MovementComponent::getState(const unsigned short state) const {

    switch (state) {
        case IDLE:
            if(this->velocity.x == 0.f && this->velocity.y == 0.f) {
                return true;
            }
            break;

        case MOVING:
            if(this->velocity.x != 0.f || this->velocity.y != 0.f) {
                return true;
            }
            break;

        case MOVING_LEFT:
            if(this->velocity.x < 0.f) {
                return true;
            }
            break;

        case MOVING_RIGHT:
            if(this->velocity.x > 0.f) {
                return true;
            }
            break;
        case MOVING_DOWN:
            if(this->velocity.y > 0.f) {
                return true;
            }
            break;
        case MOVING_UP:
            if(this->velocity.y < 0.f) {
                return true;
            }
            break;
    }

    return false;
}


void MovementComponent::move(const float dir_x, const float dir_y, const float& dt) {
    //Accelerating a sprite until max velocity
    this->velocity.x += this->acceleration * dir_x;
    this->velocity.y += this->acceleration * dir_y;
}

void MovementComponent::update(const float &dt) {
    //Decelerates the sprite and control max velocity and move the sprite

    if (this->velocity.x > 0.f) { //check for positive x
        //Max velocity check positive
        if(this->velocity.x > this->maxVelocity) {
            this->velocity.x = this->maxVelocity;
        }
        //Deceleration x positive
        this->velocity.x -= deceleration;
        if(this->velocity.x < 0.f) {
            this->velocity.x = 0.f;
        }
    } else if(this->velocity.x < 0.f) { //Check for negative X
        //Max Velocity check X negative
        if(this->velocity.x < -this->maxVelocity) {
            this->velocity.x = -this->maxVelocity;
        }
        //Deceleration X negative
        this->velocity.x += deceleration;
        if(this->velocity.x > 0.f) {
            this->velocity.x = 0.f;
        }
    }

    if (this->velocity.y > 0.f) { //check for positive Y
        //Max velocity check positive
        if(this->velocity.y > this->maxVelocity) {
            this->velocity.y = this->maxVelocity;
        }
        //Deceleration Y positive
        this->velocity.y -= deceleration;
        if(this->velocity.y < 0.f) {
            this->velocity.y = 0.f;
        }
    } else if(this->velocity.y < 0.f) { //Check for negative Y
        //Max Velocity check Y negative
        if(this->velocity.y < -this->maxVelocity) {
            this->velocity.y = -this->maxVelocity;
        }
        //Deceleration Y negative
        this->velocity.y += deceleration;
        if(this->velocity.y > 0.f) {
            this->velocity.y = 0.f;
        }
    }

    //Final Move
    this->sprite.move(this->velocity * dt); // Uses velocity
}











