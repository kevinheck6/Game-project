//
// Created by kevin on 29.10.2021.
//
#pragma once

#include "State.h"
#include "../Resources/Button.h"

class EditorState :
        public State {
private:
    //Variables
    sf::Font font;

    std::map<std::string, Button*> buttons;

    //Functions
    void initVariables();
    void initBackground();
    void initFonts();
    void initKeyBinds();
    void initButtons();

public:
    EditorState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~EditorState();

    //Functions
    void updateInput(const float& dt);
    void updateButtons();
    void update(const float& dt);
    void renderButtons(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = nullptr);


};

