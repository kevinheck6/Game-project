#pragma once

enum movement_states { IDLE = 0, MOVING, MOVING_LEFT, MOVING_RIGHT, MOVING_UP, MOVING_DOWN };

class MovementComponent {
private:
	sf::Sprite& sprite;

	float velocityMax;
	float accelerationComponent;
	float decelerationComponent;

	sf::Vector2f velocity;


public:
	MovementComponent(sf::Sprite& sprite, 
		float maxVelocity, float acceleration, float deceleration);
	virtual ~MovementComponent();

	//Accessors
	const float& getVelocityMax() const;
	const sf::Vector2f& getVelocity() const;

	//Functions
	bool getState(short unsigned state) const;
	void makeNullVelocityX();
	void makeNullVelocityY();

	void move(float x, float y, const float& dt);
	void update(const float& dt);
};

