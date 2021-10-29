//
// Created by kevin on 24.10.2021.
//

#include "Player.h"

//Initializers
void Player::initVariables() {

}

void Player::initComponents() {

}


//Constructor/Destructors
Player::Player(float x, float y,sf::Texture& texture_sheet) {
    this->initVariables();

    this->setPositions(x, y);

    this->createMovementComponent(300.f, 15.f, 5.f);
    this->createAnimationComponent(texture_sheet);

    this->animationComponent->addAnimation("IDLE_LEFT", 10.f,
                                           0, 0,
                                           10, 0, 180, 180);

    this->animationComponent->addAnimation("WALK_LEFT", 10.f,
                                           2, 1,
                                           7, 1, 180, 180);
}

Player::~Player() {

}

//Functions
void Player::update(const float &dt) {

    this->movementComponent->update(dt);
    if(this->movementComponent ->idle()) {
        this->animationComponent->play("IDLE_LEFT", dt);
    } else {
        this->animationComponent->play("WALK_LEFT", dt);
    }
}
