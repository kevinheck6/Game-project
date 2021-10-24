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
    float maxVelocity;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    sf::Vector2f deceleration;

    //Initializer Functions

public:
    MovementComponent(float maxVelocity);
    virtual ~MovementComponent();

    //Accessors
    const sf::Vector2f& getVelocity() const;

    //Functions
    void move(const float x, const float y);
    void update(const float& dt);

};

