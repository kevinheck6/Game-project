#include "../Head Files/PreCompiledHeaders.h"
#include "../Entities/Entity.h"

void Entity::initVariables() {
    animation = nullptr;
    hitBox = nullptr;
    movement = nullptr;
}

Entity::Entity() {
	this->initVariables();
}

Entity::~Entity() {
    delete this->animation;
	delete this->hitBox;
	delete this->movement;
}

//Component functions

void Entity::createHitBox(sf::Sprite & sprite, float offset_x, float offset_y,
                          float width, float height) {
    hitBox = new HitBoxComponent(sprite, offset_x, offset_y, width, height);
}

void Entity::createMovement(const float maxVelocity, const float acceleration,
                            const float deceleration) {
    movement = new MovementComponent(sprite, maxVelocity, acceleration, deceleration);
}

void Entity::createAnimation(sf::Texture & texture_sheet) {
    animation = new AnimationComponent(sprite, texture_sheet);
}

const sf::Vector2f & Entity::getPosition() const {
	if (hitBox)
		return hitBox->getPosition();

	return sprite.getPosition();
}

sf::Vector2i Entity::getGridPosition(const int gridSizeI) const {
	if (hitBox) {
        return {
                static_cast<int>(hitBox->getPosition().x) / gridSizeI,
                static_cast<int>(hitBox->getPosition().y) / gridSizeI
        };
    } else {
        return {
                static_cast<int>(sprite.getPosition().x) / gridSizeI,
                static_cast<int>(sprite.getPosition().y) / gridSizeI
        };
    }
}

sf::FloatRect Entity::getGlobalBounds() const {
	if (hitBox) {
        return hitBox->getGlobalBounds();
    }
	return sprite.getGlobalBounds();
}

sf::FloatRect Entity::getFuturePositionBounds(const float& dt) const {
	if (hitBox && movement) {
        return hitBox->getFuturePosition(movement->getVelocity() * dt);
    } else {
        return {-1.f, -1.f, -1.f, -1.f};
    }

}

//Functions
void Entity::setPosition(const float x, const float y) {
	if (hitBox) {
        hitBox->setPosition(x, y);
    } else {
        sprite.setPosition(x, y);
    }
}

void Entity::move(const float dir_x, const float dir_y, const float& dt) {
	if (movement) {
        movement->move(dir_x, dir_y, dt);
    }
}



void Entity::makeNullVelocityX() {
	if (movement) {
        movement->makeNullVelocityX();
    }
}

void Entity::makeNullVelocityY() {
	if (movement) {
        movement->makeNullVelocityY();
    }
}

void Entity::update(const float & dt)
{

}

void Entity::render(sf::RenderTarget& target)
{

}
