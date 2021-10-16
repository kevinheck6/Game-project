#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>


// Class that will work as game Engine
class Game {

private:
    //variable
    sf::RenderWindow* window;
    sf::Event sfEvent;
    sf::Clock dtClock;

    float dt; // Delta time

    //private functions
    void initVariable(); //initialize Variables
    void initWindow(); //initialize Window

public:
    Game(); //Constructor
    virtual ~Game(); //Destructor

    //Accessors

    //Functions
    void updateSFMLEvents();
    void update();
    void updateDT();

    void render();
    void run();
};


