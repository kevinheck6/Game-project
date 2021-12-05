#pragma once

#include "../Head Files/PreCompiledHeaders.h"
#include "../Components/HitBoxComponent.h"
#include "../Components/MovementComponent.h"
#include "../Components/AnimationComponent.h"

class HitBoxComponent;
class MovementComponent;
class AnimationComponent;

class Entity
{
private:
	void initVariables();

protected:

	sf::Sprite sprite;

	HitBoxComponent* hitboxComponent{};
	MovementComponent* movementComponent{};
	AnimationComponent* animationComponent{};

public:
	Entity();
	virtual ~Entity();

	//Component functions
	void createHitboxComponent(sf::Sprite& sprite, 
		float offset_x, float offset_y,
		float width, float height);
	void createMovementComponent(float maxVelocity, float acceleration, float deceleration);
	void createAnimationComponent(sf::Texture& texture_sheet);

	//Accessors
	virtual const sf::Vector2f& getPosition() const;
	virtual sf::Vector2i getGridPosition(int gridSizeI) const;
	virtual sf::FloatRect getGlobalBounds() const;
	virtual sf::FloatRect getNextPositionBounds(const float& dt) const;

	//Modifiers
	virtual void setPosition(float x, float y);
	
	//Functions
	virtual void move(float x, float y, const float& dt);
	virtual void stopVelocityX();
	virtual void stopVelocityY();

	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget& target) = 0;
};

