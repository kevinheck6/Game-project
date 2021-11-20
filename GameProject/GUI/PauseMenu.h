//
// Created by kevin on 13.11.2021.
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

#include "../Resources/Button.h"

class PauseMenu {
private:
    sf::Font& font;
    sf::Text menuText;

    sf::RectangleShape background;
    sf::RectangleShape container;

    std::map<std::string, gui::Button*> buttons;

    //Private Functions

public:
    PauseMenu(sf::RenderWindow& window, sf::Font& font);
    virtual ~PauseMenu();

    //Accessor
    std::map<std::string, gui::Button*>& getButtons();

    //Functions
    const bool isButtonPressed(const std::string key);
    void addButton(const std::string key, float y, const std::string text);
    void update(const sf::Vector2f& mousePos);
    void render(sf::RenderTarget& target);
};

