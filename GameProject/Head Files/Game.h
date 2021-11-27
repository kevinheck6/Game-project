#pragma once

#include "../States/MainMenuState.h"
//#include "../States/GameState.h"

// Class that will work as game Engine
class Game {

private:

    //variable
    GraphSettings graphSettings;
    StateData stateData;
    sf::RenderWindow* window;
    sf::Event sfEvent;

    sf::Clock dtClock;
    float dt; // Delta time

    std::stack<State*> states;

    std::map<std::string, int> supportedKeys;

    float gridSize;

    //Initialization
    void initVariables(); //initialize Variables
    void initGraphSettings(); // Initialize Graph settings
    void initWindow(); //initialize Window
    void initKeys(); // initialize Keys
    void initStateData();// Initialize State data
    void initStates(); //initialize States


public:
    //   Constructor/Destructor
    Game();
    virtual ~Game();

    //   Functions
    //Regular
    void endApplication();

    //Update
    void updateSFMLEvents();
    void update();
    void updateDT();

    //Render
    void render();

    //Core
    void run();
};


