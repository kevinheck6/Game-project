//
// Created by kevin on 22.10.2021.
//

#pragma once

#include "GameState.h"
#include "../Resources/Button.h"

class MainMenuState :
        public State {

private:
    //Variables
    sf::RectangleShape background;
    sf::Font font;

    Button *gameState_btn;

    //Functions
    void initFonts();
    void initKeyBinds();

public:
    MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys);
    virtual ~MainMenuState();

    //Functions
    void endState();

    void updateInput(const float& dt);
    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);
};

