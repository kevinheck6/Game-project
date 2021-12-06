#include "../Head Files/PreCompiledHeaders.h"
#include "../Entities/Player.h"

//Initializer functions
void Player::initVariables() {
    isAttacking = false;
}

Player::Player(float x, float y, sf::Texture& texture_sheet) {
	initVariables();

	this->setPosition(x, y);

    createHitBox(sprite, 100, 75.f, 20.f, 40.f);
    createMovement(160.f, 1000.f, 500.f);
    createAnimation(texture_sheet);

    animation->addAnimation("IDLE", 10.f,
                            0, 0,
                            10, 0, 180, 180);

    animation->addAnimation("WALK", 10.f,
                            2, 1,
                            7, 1, 180, 180);

    animation->addAnimation("ATTACK", 9.f,
                            0, 2,
                            6, 2, 180, 180);
}

Player::~Player() = default;

//Functions
void Player::updateAttack() {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        isAttacking = true;
	}
}

void Player::updateAnimation(const float & dt) {
	if (isAttacking) {
        //Set origin depending on facing direction
        if(sprite.getScale().x > 0.f) { //facing right
            sprite.setOrigin(0.f,0.f);
        } else { // Facing left
            sprite.setOrigin( 220.f, 0.f);
        }
		//Animate and check for animation end
		if (animation->play("ATTACK", dt, true)) {
            isAttacking = false;
            if(sprite.getScale().x > 0.f) { //facing right
                sprite.setOrigin(0.f,0.f);
            } else { // Facing left
                sprite.setOrigin(220.f, 0.f);
            }
        }
    }
	if (movement->getState(IDLE)) {
		animation->play("IDLE", dt);
	} else if(movement->getState(MOVING_RIGHT)) {
        if (sprite.getScale().x < 0.f) {
            sprite.setOrigin(0.f, 0.f);
            sprite.setScale(1.f,1.f);
        }

        this->animation->play("WALK", dt, movement->getVelocity().x,
                              movement->getVelocityMax());

    } else if (movement->getState(MOVING_LEFT)) {
        if (sprite.getScale().x > 0.f) {
            sprite.setOrigin(220.f, 0.f);
            sprite.setScale(-1.f, 1.f);
        }

		animation->play("WALK", dt, movement->getVelocity().x,
                        movement->getVelocityMax());
	} else if (movement->getState(MOVING_UP)) { // If character is moving up animation
		animation->play("WALK", dt,
                        movement->getVelocity().y,
                        movement->getVelocityMax());
	} else if (movement->getState(MOVING_DOWN)) { // If character is moving down animation
        animation->play("WALK", dt,
                        movement->getVelocity().y,
                        movement->getVelocityMax());
}

}

void Player::update(const float & dt) {
	movement->update(dt);
    updateAttack();
    updateAnimation(dt);
    hitBox->update();
}

void Player::render(sf::RenderTarget & target) {
	target.draw(sprite);
    hitBox->render(target);
}
