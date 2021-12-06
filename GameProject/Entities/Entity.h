#pragma once

#include "../Head Files/PreCompiledHeaders.h"
#include "../Components/HitBoxComponent.h"
#include "../Components/MovementComponent.h"
#include "../Components/AnimationComponent.h"

class HitBoxComponent;
class MovementComponent;
class AnimationComponent;

class Entity {
private:
	void initVariables();

protected:
	sf::Sprite sprite;
	HitBoxComponent* hitBox;
	MovementComponent* movement;
	AnimationComponent* animation;

public:
	Entity();
	virtual ~Entity();

	//Component functions
	void createHitBox(sf::Sprite& sprite,
                      float offset_x, float offset_y,
                      float width, float height);
	void createMovement(float maxVelocity, float acceleration, float deceleration);
	void createAnimation(sf::Texture& texture_sheet);

	//Accessors
	virtual const sf::Vector2f& getPosition() const;
	virtual sf::Vector2i getGridPosition(int gridSizeI) const;
	virtual sf::FloatRect getGlobalBounds() const;
	virtual sf::FloatRect getFuturePositionBounds(const float& dt) const;

	//Modifiers
	virtual void setPosition(float x, float y);
	
	//Functions
	virtual void move(float x, float y, const float& dt);
	virtual void makeNullVelocityX();
	virtual void makeNullVelocityY();
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget& target) = 0;
};

