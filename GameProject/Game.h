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
    //Window
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    sf::Event event;

    //Mouse Positions
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

    //Resources
    sf::Font font;

    //Text
    sf::Text uiText;

    //game logic
    bool endGame;
    unsigned points;
    float enemySpawnTimer;
    float enemySpawnTimerMax;
    int maxEnemies;
    bool mouseHeld;
    int health;

    //game objects
    std::vector<sf::RectangleShape> enemies;
    sf::RectangleShape enemy;

    //private functions
    void initVariable(); //initialize Variables
    void initWindow(); //initialize Window
    void intEnemies(); //initialize Enemies
    void initFonts(); //initialize Fonts
    void initText(); //initialize Text

public:
    Game(); //Constructor
    virtual ~Game(); //Destructor

    //Accessors
    const bool running() const;
    const bool getEndGame() const;

    //Functions
    void spawnEnemy();
    void pollEvents();

    void updateText();
    void updateMousePositions();
    void updateEnemies();
    void update();

    void renderEnemies(sf::RenderTarget& target);
    void render();
    void renderText(sf::RenderTarget& target);

};


