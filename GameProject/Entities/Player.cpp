//
// Created by kevin on 24.10.2021.
//

#include "Player.h"

//Initializers
void Player::initVariables() {

}

void Player::initComponents() {
    this->createMovementComponent(100.f);
}


//Constructor/Destructors
Player::Player(float x, float y,sf::Texture* texture) {
    this->initVariables();
    this->initComponents();
    this->createSprite(texture);
    this->setPositions(x, y);
}

Player::~Player() {

}
