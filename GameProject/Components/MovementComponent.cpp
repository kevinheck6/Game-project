#include "../Head Files/PreCompiledHeaders.h"
#include "../Components/MovementComponent.h"

MovementComponent::MovementComponent(sf::Sprite& sprite, 
	float maxVelocity, float acceleration, float deceleration)
	: sprite(sprite),
      velocityMax(maxVelocity), accelerationComponent(acceleration), decelerationComponent(deceleration) {
	
}

MovementComponent::~MovementComponent() = default;

//Accessors
const float & MovementComponent::getVelocityMax() const {
	return velocityMax;
}

const sf::Vector2f & MovementComponent::getVelocity() const {
	return velocity;
}

//Functions
bool MovementComponent::getState(const short unsigned state) const {
	switch (state) {
	case IDLE:
		if (velocity.x == 0.f && velocity.y == 0.f) {
            return true;
        }
		break;

	case MOVING:
		if (velocity.x != 0.f || velocity.y != 0.f) {
            return true;
        }
		break;

	case MOVING_LEFT:
		if (velocity.x < 0.f){
            return true;
        }
		break;

	case MOVING_RIGHT:
		if (velocity.x > 0.f){
            return true;
        }
		break;

	case MOVING_UP:
		if (velocity.y < 0.f) {
            return true;
        }
		break;

	case MOVING_DOWN:
		if (velocity.y > 0.f) {
            return true;
        }
		break;

	}
	return false;
}

void MovementComponent::makeNullVelocityX() {
	// Stops the velocity in X */
	velocity.x = 0.f;
}

void MovementComponent::makeNullVelocityY() {
	// Stops the velocity in Y
	velocity.y = 0.f;
}

void MovementComponent::move(const float dir_x, const float dir_y, const float& dt) {
	//using the Acceleration for smooth
	velocity.y += accelerationComponent * dir_y * dt;
    velocity.x += accelerationComponent * dir_x * dt;
}

void MovementComponent::update(const float & dt) {
	//Moves the sprite.
    // Positive x
	if (velocity.x > 0.f) {
		//Max velocity
		if (velocity.x > velocityMax) {
            velocity.x = velocityMax;
        }
		//Deceleration for X
		velocity.x -= decelerationComponent * dt;
		if (velocity.x < 0.f) {
            velocity.x = 0.f;
        }
	}
        //Negative x
	else if(velocity.x < 0.f) {
		//Max velocity
		if (velocity.x < -velocityMax) {
            velocity.x = -velocityMax;
        }

		//Deceleration for X
		velocity.x += decelerationComponent * dt;
		if (velocity.x > 0.f) {
            velocity.x = 0.f;
        }
	}

    //Positive y
	if (velocity.y > 0.f) {
		//Max velocity
		if (velocity.y > velocityMax) {
            velocity.y = velocityMax;
        }

		//Deceleration
		velocity.y -= decelerationComponent * dt;
		if (velocity.y < 0.f) {
            velocity.y = 0.f;
        }
	}
    //Negative Y
	else if (velocity.y < 0.f) {
		//Max velocity
		if (velocity.y < -velocityMax) {
            velocity.y = -velocityMax;
        }

		//Deceleration for Y
		velocity.y += decelerationComponent * dt;
		if (velocity.y > 0.f) {
            velocity.y = 0.f;
        }
	}

	//Movement itself result
	sprite.move(velocity * dt);
}
