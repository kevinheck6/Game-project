//
// Created by kevin on 22.10.2021.
//
#include "MainMenuState.h"

void MainMenuState::initFonts() {
    if(!this->font.loadFromFile("/home/kevin/CLionProjects/Game-projecttest/GameProject/Fonts/Amatic-Bold.ttf")) {
        throw("ERROR - MainMenuState - Could not load");
    }


}

void MainMenuState::initKeyBinds() {

    std::ifstream ifs("/home/kevin/CLionProjects/Game-projecttest/GameProject/Config/GameState_KeyBind.ini");
    if (ifs.is_open()) {
        std::string key = "";
        std::string key2 = "";
        while (ifs >> key >> key2) {
            this->keyBinds[key] = this->supportedKeys->at(key2);
        }
    }
    ifs.close();

}

MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys)
        : State(window, supportedKeys) {
    this->initFonts();
    this->initKeyBinds();

    this->gameState_btn = new Button(100,100, 150, 50,  &this->font, "New Game",
                                     sf::Color(70, 70, 150, 200),
                                     sf::Color(70, 200, 200, 200),
                                     sf::Color(150, 70, 150, 200));

    this->background.setSize(sf::Vector2f(window->getSize().x,window->getSize().y));
    this->background.setFillColor(sf::Color::White);
}

MainMenuState::~MainMenuState() {
    delete this->gameState_btn;
}

void MainMenuState::endState() {
    std::cout << "Ending game State" << "\n";
}

void MainMenuState::updateInput(const float &dt) {
    this->checkForQuit();

}

void MainMenuState::update(const float& dt) {
    this->updateMousePosition();
    this->updateInput(dt);

    this->gameState_btn->update(this->mousePosView);
}

void MainMenuState::render(sf::RenderTarget* target) {
    if(!target) {
        target = this->window;
    }
    target->draw(this->background);
    this->gameState_btn->render(target);
}




