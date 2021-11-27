//
// Created by kevin on 24.10.2021.
//
#include "../Head Files/PreCompiledHeaders.h"
#include "Player.h"

//Initializers
void Player::initVariables() {
    this->attacking = false;
}

void Player::initComponents() {

}


//Constructor/Destructors
Player::Player(float x, float y,sf::Texture& texture_sheet) {
    this->initVariables();

    this->setPosition(x, y);

    this->createHitBoxComponent(this->sprite, 0.f, 0.f,
                                20.f, 40.f);
    this->createMovementComponent(300.f, 15.f, 10.f);
    this->createAnimationComponent(texture_sheet);

    this->animationComponent->addAnimation("IDLE", 10.f,
                                           0, 0,
                                           10, 0, 180, 180);

    this->animationComponent->addAnimation("WALK", 10.f,
                                           2, 1,
                                           7, 1, 180, 180);

    this->animationComponent->addAnimation("ATTACK", 9.f,
                                           0, 2,
                                           6, 2, 180, 180);
}

Player::~Player() {

}

//Functions
void Player::updateAttack() {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        this->attacking = true;
    }
}

void Player::updateAnimations(const float &dt) {
    if(this->attacking) {
        //Set origin depending on facing direction
        if(this->sprite.getScale().x > 0.f) { //facing right
            this->sprite.setOrigin(100,75.f);
        } else { // Facing left
            this->sprite.setOrigin( 100.f, 75.f);
        }
        //Animate and check for animation end
        if(this->animationComponent->play("ATTACK", dt, true)) {
            this->attacking = false;
            if(this->sprite.getScale().x > 0.f) { //facing right
                this->sprite.setOrigin(100.f,75.f);
            } else { // Facing left
                this->sprite.setOrigin(120, 75.f);
            }
        }
    }
    if(this->movementComponent ->getState(IDLE)) {
        this->animationComponent->play("IDLE", dt);

    } else if(this->movementComponent->getState(MOVING_RIGHT)) {
        if (this->sprite.getScale().x < 0.f) {
            this->sprite.setOrigin(100.f, 75.f);
            this->sprite.setScale(1.f,1.f);
        }
        this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x,
                                       this->movementComponent->getMaxVelocity());

    } else if (this->movementComponent->getState(MOVING_LEFT)) {
        if (this->sprite.getScale().x > 0.f) {
            this->sprite.setOrigin(120.f, 75.f);
            this->sprite.setScale(-1.f, 1.f);
        }
        this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x,
                                       this->movementComponent->getMaxVelocity());

    } else if (this->movementComponent->getState(MOVING_UP)) {
        this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().y,
                                       this->movementComponent->getMaxVelocity());

    } else if (this->movementComponent->getState(MOVING_DOWN)) {
        this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().y,
                                       this->movementComponent->getMaxVelocity());

    }
}

void Player::update(const float &dt) {

    this->movementComponent->update(dt);
    this->updateAttack();
    this->updateAnimations(dt);
    this->hitBoxComponent->update();
}

void Player::render(sf::RenderTarget &target) {
    target.draw(this->sprite);

    this->hitBoxComponent->render(target);
}


