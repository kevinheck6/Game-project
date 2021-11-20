//
// Created by kevin on 14.11.2021.
//
#pragma once

#include "State.h"
#include "../Resources/Button.h"

class SettingsState :
        public State {

private:
    //Variables
    GraphSettings& graphSettings;
    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    sf::Font font;

    std::map<std::string, gui::Button*> buttons;
    std::map<std::string, gui::DropDownList*> dropDownLists;

    sf::Text optionsText;

    std::vector<sf::VideoMode> videoModes;
    //Functions
    void initVariables();
    void initBackground();
    void initFonts();
    void initKeyBinds();
    void initButtons();
    void initText();

public:
    SettingsState(sf::RenderWindow* window, GraphSettings& graphSettings,
                  std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~SettingsState();
    //Accessors

    //Functions
    void updateInput(const float& dt);
    void updateButtons(const float& dt);
    void update(const float& dt);
    void renderButtons(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = nullptr);

};

