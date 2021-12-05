#include "../Head Files/PreCompiledHeaders.h"
#include "../Entities/Entity.h"

void Entity::initVariables() {
    animationComponent = nullptr;
	hitboxComponent = nullptr;
	movementComponent = nullptr;
}

Entity::Entity() {
	this->initVariables();
}

Entity::~Entity() {
    delete this->animationComponent;
	delete this->hitboxComponent;
	delete this->movementComponent;
}

//Component functions

void Entity::createHitboxComponent(sf::Sprite & spriteE, float offset_x, float offset_y,
	float width, float height) {
	hitboxComponent = new HitBoxComponent(spriteE, offset_x, offset_y, width, height);
}

void Entity::createMovementComponent(const float maxVelocity, const float acceleration,
                                     const float deceleration) {
	movementComponent = new MovementComponent(sprite, maxVelocity, acceleration, deceleration);
}

void Entity::createAnimationComponent(sf::Texture & texture_sheet) {
	animationComponent = new AnimationComponent(sprite, texture_sheet);
}

const sf::Vector2f & Entity::getPosition() const {
	if (hitboxComponent)
		return hitboxComponent->getPosition();

	return sprite.getPosition();
}

sf::Vector2i Entity::getGridPosition(const int gridSizeI) const {
	if (hitboxComponent) {
        return {
                static_cast<int>(hitboxComponent->getPosition().x) / gridSizeI,
                static_cast<int>(hitboxComponent->getPosition().y) / gridSizeI
        };
    } else {
        return {
                static_cast<int>(sprite.getPosition().x) / gridSizeI,
                static_cast<int>(sprite.getPosition().y) / gridSizeI
        };
    }
}

sf::FloatRect Entity::getGlobalBounds() const {
	if (hitboxComponent) {
        return hitboxComponent->getGlobalBounds();
    }
	return sprite.getGlobalBounds();
}

sf::FloatRect Entity::getNextPositionBounds(const float& dt) const {
	if (hitboxComponent && movementComponent) {
        return hitboxComponent->getNextPosition(movementComponent->getVelocity() * dt);
    } else {
        return {-1.f, -1.f, -1.f, -1.f};
    }

}

//Functions
void Entity::setPosition(const float x, const float y) {
	if (hitboxComponent) {
        hitboxComponent->setPosition(x, y);
    } else {
        sprite.setPosition(x, y);
    }
}

void Entity::move(const float dir_x, const float dir_y, const float& dt) {
	if (movementComponent) {
        movementComponent->move(dir_x, dir_y, dt);
    }
}



void Entity::stopVelocityX() {
	if (movementComponent) {
        movementComponent->stopVelocityX();
    }
}

void Entity::stopVelocityY() {
	if (movementComponent) {
        movementComponent->stopVelocityY();
    }
}

void Entity::update(const float & dt)
{

}

void Entity::render(sf::RenderTarget& target)
{

}
