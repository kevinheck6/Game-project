#pragma once

#include "../States/MainMenuState.h"
//#include "../States/GameState.h"

// Class that will work as game Engine
class Game {

private:
    class GraphSettings {
    public:
        GraphSettings();
        ~GraphSettings();

        //Variable
        std::string title;
        sf::VideoMode resolution;
        bool fullScreen;
        bool verticalSync;
        unsigned frameRateLimit;
        sf::ContextSettings contextSettings;
        std::vector<sf::VideoMode> videoModes;

        //Functions
        void saveFile(const std::string path);
        void loadFile(const std::string path);
    };
    //variable
    GraphSettings graphSettings;
    sf::RenderWindow* window;
    sf::Event sfEvent;

    sf::Clock dtClock;
    float dt; // Delta time

    std::stack<State*> states;

    std::map<std::string, int> supportedKeys;

    //Initialization
    void initVariables(); //initialize Variables
    void initGraphSettings(); // Initialize Graph settings
    void initWindow(); //initialize Window
    void initKeys(); // initialize Keys
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


