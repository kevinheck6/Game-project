//
// Created by kevin on 24.10.2021.
//
#pragma once

enum movement_states {IDLE = 0, MOVING, MOVING_LEFT, MOVING_RIGHT, MOVING_UP, MOVING_DOWN};

class MovementComponent {
private:
    //Variables
    sf::Sprite& sprite;

    float maxVelocity;
    float acceleration;
    float deceleration;

    sf::Vector2f velocity;

    //Initializer Functions

public:
    MovementComponent(sf::Sprite& sprite, float maxVelocity, float acceleration, float deceleration);
    virtual ~MovementComponent();

    //Accessors
    const float& getMaxVelocity() const;
    const sf::Vector2f& getVelocity() const;

    //Functions
    const bool getState(const short unsigned state) const;
    void noVelocity();
    void noVelocityY();
    void noVelocityX();

    void move(const float x, const float y, const float& dt);
    void update(const float& dt);

};

