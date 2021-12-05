#include "../Head Files/PreCompiledHeaders.h"
#include "../Entities/Player.h"

//Initializer functions
void Player::initVariables() {
	attacking = false;
}

Player::Player(float x, float y, sf::Texture& texture_sheet) {
	initVariables();

	this->setPosition(x, y);

    createHitboxComponent(sprite, 100,75.f, 20.f, 40.f);
	createMovementComponent(160.f, 1000.f, 500.f);
	createAnimationComponent(texture_sheet);

    animationComponent->addAnimation("IDLE", 10.f,
                                           0, 0,
                                           10, 0, 180, 180);

    animationComponent->addAnimation("WALK", 10.f,
                                           2, 1,
                                           7, 1, 180, 180);

    animationComponent->addAnimation("ATTACK", 9.f,
                                           0, 2,
                                           6, 2, 180, 180);
}

Player::~Player() = default;

//Functions
void Player::updateAttack() {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		attacking = true;
	}
}

void Player::updateAnimation(const float & dt) {
	if (attacking) {
        //Set origin depending on facing direction
        if(sprite.getScale().x > 0.f) { //facing right
            sprite.setOrigin(0.f,0.f);
        } else { // Facing left
            sprite.setOrigin( 220.f, 0.f);
        }
		//Animate and check for animation end
		if (animationComponent->play("ATTACK", dt, true)) {
            attacking = false;
            if(sprite.getScale().x > 0.f) { //facing right
                sprite.setOrigin(0.f,0.f);
            } else { // Facing left
                sprite.setOrigin(220.f, 0.f);
            }
        }
    }
	if (movementComponent->getState(IDLE)) {
		animationComponent->play("IDLE", dt);
	} else if(movementComponent->getState(MOVING_RIGHT)) {
        if (sprite.getScale().x < 0.f) {
            sprite.setOrigin(0.f, 0.f);
            sprite.setScale(1.f,1.f);
        }

        this->animationComponent->play("WALK", dt, movementComponent->getVelocity().x,
                                       movementComponent->getMaxVelocity());

    } else if (movementComponent->getState(MOVING_LEFT)) {
        if (sprite.getScale().x > 0.f) {
            sprite.setOrigin(220.f, 0.f);
            sprite.setScale(-1.f, 1.f);
        }

		animationComponent->play("WALK", dt, movementComponent->getVelocity().x,
                                 movementComponent->getMaxVelocity());
	} else if (movementComponent->getState(MOVING_UP)) { // If character is moving up animation
		animationComponent->play("WALK", dt,
                                 movementComponent->getVelocity().y,
                                 movementComponent->getMaxVelocity());
	} else if (movementComponent->getState(MOVING_DOWN)) { // If character is moving down animation
        animationComponent->play("WALK", dt,
                                 movementComponent->getVelocity().y,
                                 movementComponent->getMaxVelocity());
}

}

void Player::update(const float & dt) {
	movementComponent->update(dt);
    updateAttack();
    updateAnimation(dt);
    hitboxComponent->update();
}

void Player::render(sf::RenderTarget & target) {
	target.draw(sprite);
    hitboxComponent->render(target);
}
