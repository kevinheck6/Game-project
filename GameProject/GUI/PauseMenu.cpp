//
// Created by kevin on 13.11.2021.
//
#include "../Head Files/PreCompiledHeaders.h"
#include "PauseMenu.h"

PauseMenu::PauseMenu(sf::RenderWindow& window, sf::Font& font)
: font(font) {
    //Initialize Background
    this->background.setSize(sf::Vector2f(
            static_cast<float>(window.getSize().x) ,
            static_cast<float>(window.getSize().y)));

    this->background.setFillColor(sf::Color(20,20,20,100));

    //Initialize Container
    this->container.setSize(sf::Vector2f(
            static_cast<float>(window.getSize().x) / 4.f,
            static_cast<float>(window.getSize().y) - 100.f));

    this->container.setFillColor(sf::Color(20,20,20,200));
    this->container.setPosition(
            static_cast<float>(window.getSize().x) / 2.f - this->container.getSize().x/2,
            30.f);


    //Init Text
    this->menuText.setFont(font);
    this->menuText.setFillColor(sf::Color(255, 255, 255, 100));
    this->menuText.setCharacterSize(30);
    this->menuText.setString("PAUSE");
    this->menuText.setPosition(
            this->container.getPosition().x +
            this->container.getSize().x / 2.f - this->menuText.getGlobalBounds().width / 2.f,
            this->container.getPosition().y + 40.f);

}

PauseMenu::~PauseMenu() {
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end(); ++it) {
        delete it->second;
    }
}

std::map<std::string, gui::Button *> &PauseMenu::getButtons() {
    return this->buttons;
}

//Functions
const bool PauseMenu::isButtonPressed(const std::string key) {
    return this->buttons[key]->isPressed();
}

void PauseMenu::addButton(const std::string key, float y, const std::string text) {
    float width = 250.f;
    float height = 68.f;
    float x = this->container.getPosition().x + this->container.getSize().x / 2.f - width / 2.f;

    this->buttons[key] = new gui::Button(
            x, y, width, height,
            &this->font,text, 70,
            sf::Color(250, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
            sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(150, 20, 20, 0));

}

void PauseMenu::update(const sf::Vector2i& mousePosWindow) {
    for (auto &i :this->buttons) {
        i.second->update(mousePosWindow);
    }
}

void PauseMenu::render(sf::RenderTarget &target) {
    target.draw(this->background);
    target.draw(this->container);

    for(auto &i : this->buttons) {
        i.second->render(target);
    }

    target.draw(this->menuText);
}




