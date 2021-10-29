//
// Created by kevin on 24.10.2021.
//
#pragma once

#include <iostream>
#include <ctime>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <stack>
#include <map>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>


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
    const sf::Vector2f& getVelocity() const;

    //Functions
    const bool idle() const;

    void move(const float x, const float y, const float& dt);
    void update(const float& dt);

};

