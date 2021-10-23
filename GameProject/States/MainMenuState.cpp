//
// Created by kevin on 22.10.2021.
//
#include "MainMenuState.h"

void MainMenuState::initFonts() {
    if(!this->font.loadFromFile("../Fonts/Amatic-Bold.ttf")) {
        throw("ERROR - MainMenuState - Could not load");
    }


}

void MainMenuState::initKeyBinds() {

    std::ifstream ifs("../Config/MainMenuState_KeyBinds.ini");
    if (ifs.is_open()) {
        std::string key = "";
        std::string key2 = "";
        while (ifs >> key >> key2) {
            this->keyBinds[key] = this->supportedKeys->at(key2);
        }
    }
    ifs.close();
}

void MainMenuState::initButtons() {

    this->buttons["GAME_STATE"] = new Button(100,100, 150, 50,
                                                    &this->font,"New Game",
                                     sf::Color(70, 70, 150, 200),
                                     sf::Color(70, 200, 200, 200),
                                     sf::Color(150, 70, 150, 200));

    this->buttons["EXIT_STATE"] = new Button(100,300, 150, 50,
                                             &this->font,"Exit game",
                                             sf::Color(70, 70, 150, 200),
                                             sf::Color(70, 200, 200, 200),
                                             sf::Color(150, 70, 150, 200));
}


MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
        : State(window, supportedKeys, states) {
    this->initFonts();
    this->initKeyBinds();
    this->initButtons();


    this->background.setSize(sf::Vector2f(window->getSize().x,window->getSize().y));
    this->background.setFillColor(sf::Color::White);
}

MainMenuState::~MainMenuState() {
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end(); ++it) {
        delete it->second;
    }
}

void MainMenuState::endState() {
    std::cout << "Ending MainMenuState" << "\n";
}

void MainMenuState::updateInput(const float &dt) {
    this->checkForQuit();

}

void MainMenuState::updateButtons() {
    //update all buttons on this state and handle their functionality
    for(auto &it : this->buttons) {
        it.second->update(this->mousePosView);
    }
    //New Game
    if(this->buttons["GAME_STATE"]->isPressed()) {
        this->states->push(new GameState(this->window, this->supportedKeys, this->states));
    }

    //Quit The Game
    if(this->buttons["EXIT_STATE"]->isPressed()) {
        this->quit = true;
    }
}

void MainMenuState::update(const float& dt) {
    this->updateMousePosition();
    this->updateInput(dt);

    this->updateButtons();

}

void MainMenuState::renderButtons(sf::RenderTarget *target) {
    for(auto it : this->buttons) {
        it.second->render(target);
    }
}

void MainMenuState::render(sf::RenderTarget* target) {
    if(!target) {
        target = this->window;
    }
    target->draw(this->background);

    this->renderButtons(target);
}









